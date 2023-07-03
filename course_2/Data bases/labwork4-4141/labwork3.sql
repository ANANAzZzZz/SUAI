-- Лабораторная работа №3, дисциплина "Базы данных", СПбГУАП, весенний семестр 2023

-- Включение форсирования ограничений ссылочной целостности
PRAGMA foreign_keys = ON;

-- Очистка схемы данных
DROP TABLE IF EXISTS Room_type_in_Trip;
DROP TABLE IF EXISTS Excursion_in_Trip;
DROP TABLE IF EXISTS Trip;
DROP TABLE IF EXISTS Station;
DROP TABLE IF EXISTS Room_type;
DROP TABLE IF EXISTS Contract;
DROP TABLE IF EXISTS Tourist_group;
DROP TABLE IF EXISTS Excursion;
DROP TABLE IF EXISTS Hotel;
DROP TABLE IF EXISTS City;
DROP TABLE IF EXISTS Client;
DROP TABLE IF EXISTS Route;
DROP TABLE IF EXISTS Country;

DROP VIEW IF EXISTS international_routes_stations_count_in_cities;
DROP VIEW IF EXISTS Clients_travelling_alone_and_stay_in_lux;
DROP VIEW IF EXISTS Clients_with_different_routes_and_only_country_without_excursions;

-- Создание схемы данных
CREATE TABLE Client (
		phone_number INTEGER PRIMARY KEY,
		full_name VARCHAR(30),
		adress VARCHAR,
		date_of_birth DATE
);
	
CREATE TABLE Contract (
		contract_number INTEGER PRIMARY KEY,
		date_of_conclusion DATE,
		payment_method VARCHAR(30),
		clients_phone_number INTEGER REFERENCES Client(phone_number) ON UPDATE CASCADE
);

CREATE TABLE Trip (
		trip_number INTEGER PRIMARY KEY,
		price MONEY,
		group_number INTEGER REFERENCES Tourist_group(group_number) ON UPDATE CASCADE,
		clients_phone_number INTEGER REFERENCES Client(phone_number) ON UPDATE CASCADE,
		contract_number INTEGER REFERENCES Contract(contract_number) ON UPDATE CASCADE,
		insured_sum MONEY CHECK(insured_sum <= 0.3 * price)
);

CREATE TABLE Tourist_group (
		group_number INTEGER PRIMARY KEY,
		travel_date DATE,
		route_name VARCHAR(30) REFERENCES Route(name) ON UPDATE CASCADE,
		min_count INTEGER CHECK(min_count < max_count), 
		max_count INTEGER
);

CREATE TABLE Route (
		name VARCHAR(30) PRIMARY KEY,
		price MONEY,
		duration INTEGER,
		start_date DATE,
		end_date DATE
);

CREATE TABLE Station (
		station_number INTEGER,
		route_name VARCHAR(30) REFERENCES Route(name) ON UPDATE CASCADE,
		duration INTEGER,
		city_name VARCHAR(30) REFERENCES City(name) ON UPDATE CASCADE,
		PRIMARY KEY(station_number, route_name)
);

CREATE TABLE City (
		name VARCHAR(30) PRIMARY KEY,
		country_name VARCHAR(30) REFERENCES Country(name) ON UPDATE CASCADE
);

CREATE TABLE Country (
		name VARCHAR(30) PRIMARY KEY
);

CREATE TABLE Hotel (
		name VARCHAR(30),
		city_name VARCHAR(30) REFERENCES City(name) ON UPDATE CASCADE,
		PRIMARY KEY(name, city_name)
);

CREATE TABLE Excursion (
		name VARCHAR(30),
		excursion_date DATE,
		city_name VARCHAR(30), 
		PRIMARY KEY(name, city_name),
		FOREIGN KEY(city_name) REFERENCES City(name) ON UPDATE CASCADE
);

CREATE TABLE Excursion_in_Trip (
		excursion_name VARCHAR(30),
		trip_number INTEGER(30),
		city_name_in_excursion VARCHAR(30),
		PRIMARY KEY(excursion_name, trip_number, city_name_in_excursion),
		FOREIGN KEY(excursion_name, city_name_in_excursion) REFERENCES Excursion(name, city_name) ON UPDATE CASCADE,
		FOREIGN KEY(trip_number) REFERENCES Trip(trip_number) ON UPDATE CASCADE
);

CREATE TABLE Room_type (
		name VARCHAR(30),
		city_name_of_hotel VARCHAR(30),
		hotel_name VARCHAR(30),
		PRIMARY KEY(name, city_name_of_hotel, hotel_name),
    FOREIGN KEY(city_name_of_hotel, hotel_name) REFERENCES Hotel(city_name, name) ON UPDATE CASCADE
);

CREATE TABLE Room_type_in_Trip (
		trip_number INTEGER(30),
		room_type_name VARCHAR(30),
		city_name_of_hotel VARCHAR(30),
		hotel_name VARCHAR(30),
		PRIMARY KEY(trip_number, room_type_name, city_name_of_hotel, hotel_name),
		FOREIGN KEY(trip_number) REFERENCES Trip(trip_number) ON UPDATE CASCADE,
		FOREIGN KEY(room_type_name, city_name_of_hotel, hotel_name) REFERENCES Room_type(name, city_name_of_hotel, hotel_name) ON UPDATE CASCADE
);

-- Заполнение данными
INSERT INTO Client(phone_number, full_name, adress, date_of_birth) VALUES
		(182546325, 'Павлов Д.А.', 'Московский пр. 133', '1990-12-31'),
		(189331233, 'Иванов В.В.', 'Литейный пр. 222', '2000-02-15'),
		(883137531, 'Петров И.И.', 'Ленсовета 35', '1996-10-22'),
		(884142599, 'Сыворотнев В.С.', 'Новоизмайловский 16', '2003-4-26'),
		(887571244, 'Сидоров А.А.', 'Варшавска 12а', '2001-05-03');
		
INSERT INTO Contract(contract_number, date_of_conclusion, payment_method, clients_phone_number) VALUES
		(1, '2023-04-05', 'Карта', '884142599'), -- 3
		(2, '2023-01-17', 'Карта', '189331233'),
		(3, '2021-09-08', 'Наличные', '883137531'),
		(4, '2021-06-22', 'Карта', '887571244'),
		(5, '2022-07-31', 'Наличные', '182546325');

INSERT INTO Route(name, price, duration, start_date, end_date) VALUES
		('Две страны', 50000, 10, '2023-04-05', '2023-04-15'),
		('Одна страна', 35000, 6, '2023-03-05', '2023-03-11'),
		('Три страны', 70000, 15, '2023-05-01', '2023-05-15'),
		('Одна страна, 2 города', 15000, 7, '2023-03-05', '2023-05-10');
		
INSERT INTO Tourist_group(group_number, travel_date, route_name, min_count, max_count) VALUES
		(1, '2023-04-05', 'Две страны', 0, 3),
		(2, '2023-03-05', 'Одна страна', 1, 10),
		(3, '2023-05-01', 'Три страны', 1, 10),
		(0, '2023-01-01', 'Одна страна, 2 города', 1, 10);

INSERT INTO Trip(trip_number, price, group_number, clients_phone_number, contract_number, insured_sum) VALUES
		(1, 50000, 2, 884142599, 1, 15000), -- 3
		(2, 35000, 0, 189331233, 2, 10000),
		(4, 70000, 3, 887571244, 5, 20000),
		(5, 70000, 3, 182546325, 5, 20000),
		(7, 35000, 0, 883137531, 5, 10000),
		(8, 35000, 0, 887571244, 5, 10000),
    (9, 50000, 0, 884142599, 1, 15000);

INSERT INTO Country(name) VALUES
		('Италия'),
		('Россия'),
		('Сербия'),
		('США'),
		('Египет');
		
INSERT INTO City(name, country_name) VALUES
		('Белград', 'Сербия'),
		('Вашингтон', 'США'),
		('Гиза', 'Египет'),
		('Рим', 'Италия'),
		('Санкт-Петербург', 'Россия'),
		('Каир', 'Египет'),
		('Луксор', 'Египет');

INSERT INTO Station(station_number, route_name, duration, city_name) VALUES 
		(1, 'Две страны', 5, 'Рим'),
		(2, 'Две страны', 5, 'Санкт-Петербург'),
		(1, 'Одна страна', 6, 'Гиза'),
		(1, 'Три страны', 5, 'Белград'),
		(2, 'Три страны', 5, 'Вашингтон'),
		(3, 'Три страны', 5, 'Санкт-Петербург'),
		(1, 'Одна страна, 2 города', 3, 'Каир'),
    (	2, 'Одна страна, 2 города', 4, 'Луксор');

INSERT INTO Hotel(name, city_name) VALUES
		('City hotel', 'Белград'),
		('Duo housing', 'Вашингтон'),
		('Астория', 'Санкт-Петербург'),
		('Сан-Марина', 'Рим');

INSERT INTO Excursion(name, excursion_date, city_name) VALUES
		('Белградская крепость', '2023-05-13', 'Белград'),
		('Белый дом', '2023-05-10', 'Вашингтон'),
		('Исаакиевская колоннада', '2023-03-06', 'Санкт-Петербург'),
		('Колизей', '2023-04-07', 'Рим'),
		('Эрмитаж', '2023-05-03', 'Санкт-Петербург'),
    ('Прогулка по парку', '2023-05-03', 'Белград');

INSERT INTO Excursion_in_Trip(excursion_name, trip_number, city_name_in_excursion) VALUES
		('Белградская крепость', 4, 'Белград'),
		('Белый дом', 4, 'Вашингтон'),
		('Белый дом', 5, 'Вашингтон'),
		('Исаакиевская колоннада', 2, 'Санкт-Петербург'),
		('Колизей', 2, 'Рим'),
		('Эрмитаж', 4, 'Санкт-Петербург'),
		('Эрмитаж', 5, 'Санкт-Петербург');

INSERT INTO Room_type(name, city_name_of_hotel, hotel_name) VALUES
		('Люкс', 'Вашингтон', 'Duo housing'),
		('Люкс', 'Рим', 'Сан-Марина'),
		('Люкс', 'Санкт-Петербург', 'Астория'),
		('Президентский', 'Санкт-Петербург', 'Астория'),
		('Эконом', 'Белград', 'City hotel'),
		('Эконом', 'Рим', 'Сан-Марина');

INSERT INTO Room_type_in_Trip(trip_number, room_type_name, city_name_of_hotel, hotel_name) VALUES 
		(1, 'Люкс', 'Рим', 'Сан-Марина'), -- 3
		(1, 'Люкс', 'Санкт-Петербург', 'Астория'),
		(4, 'Люкс', 'Вашингтон', 'Duo housing'),
		(4, 'Люкс', 'Санкт-Петербург', 'Астория'),
		(4, 'Эконом', 'Белград', 'City hotel'),
		(5, 'Люкс', 'Вашингтон', 'Duo housing'),
		(2, 'Люкс', 'Санкт-Петербург', 'Астория'),
    (8, 'Люкс', 'Рим', 'Сан-Марина'),
		(5, 'Эконом', 'Белград', 'City hotel');

CREATE VIEW Clients_travelling_alone_and_stay_in_lux AS
SELECT DISTINCT full_name
FROM Trip, Client
Where Client.Phone_number = Trip.clients_phone_number
      -- клиенты,в договоре у которых нет других людей с путевками
      AND Trip.clients_phone_number IN (
          SELECT Trip.clients_phone_number
          FROM Trip
          GROUP BY contract_number
          HAVING COUNT(DISTINCT Trip.clients_phone_number) = 1
      )
      AND trip_number NOT IN (
          -- клинеты, останавливавшиеся не только в люксе
          SELECT trip_number
          FROM Room_type_in_Trip
          GROUP BY trip_number, city_name_of_hotel
          HAVING room_type_name <> 'Люкс'
      );