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
		(1, '2023-04-05', 'Карта', '884142599'),
		(2, '2023-01-17', 'Карта', '189331233'),
		(3, '2021-09-08', 'Наличные', '883137531'),
		(4, '2021-06-22', 'Карта', '887571244'),
		(5, '2022-07-31', 'Наличные', '182546325');

INSERT INTO Route(name, price, duration, start_date, end_date) VALUES
		('Две страны', 50000, 10, '2023-04-05', '2023-04-15'),
		('Одна страна', 35000, 6, '2023-03-05', '2023-03-11'),
		('Три страны', 70000, 15, '2023-05-01', '2023-05-15');
		
INSERT INTO Tourist_group(group_number, travel_date, route_name, min_count, max_count) VALUES
		(1, '2023-04-05', 'Две страны', 1, 30),
		(2, '2023-03-05', 'Одна страна', 1, 10),
		(3, '2023-05-01', 'Три страны', 2, 50);

INSERT INTO Trip(trip_number, price, group_number, clients_phone_number, contract_number, insured_sum) VALUES
		(1, 50000, 1, 884142599, 1, 15000),
		(2, 35000, 2, 189331233, 2, 10000),
		(3, 35000, 2, 883137531, 3, 10000),
		(4, 70000, 3, 887571244, 4, 20000),
		(5, 70000, 3, 182546325, 5, 20000);

INSERT INTO Country(name) VALUES
		('Австралия'),
		('Италия'),
		('Россия'),
		('Сербия'),
		('США');
		
INSERT INTO City(name, country_name) VALUES
		('Белград', 'Сербия'),
		('Вашингтон', 'США'),
		('Канберра', 'Австралия'),
		('Рим', 'Италия'),
		('Санкт-Петербург', 'Россия');

INSERT INTO Station(station_number, route_name, duration, city_name) VALUES 
		(1, 'Две страны', 5, 'Рим'),
		(2, 'Две страны', 5, 'Санкт-Петербург'),
		(3, 'Одна страна', 6, 'Канберра'),
		(4, 'Три страны', 5, 'Белград'),
		(5, 'Три страны', 5, 'Вашингтон'),
		(6, 'Три страны', 5, 'Санкт-Петербург');

INSERT INTO Hotel(name, city_name) VALUES
		('City hotel', 'Белград'),
		('Duo housing', 'Вашингтон'),
		('The Villiage', 'Канберра'),
		('Астория', 'Санкт-Петербург'),
		('Сан-Марина', 'Рим');

INSERT INTO Excursion(name, excursion_date, city_name) VALUES
		('Белградская крепость', '2023-05-13', 'Белград'),
		('Белый дом', '2023-05-10', 'Вашингтон'),
		('Исаакиевская колоннада', '2023-03-06', 'Санкт-Петербург'),
		('Колизей', '2023-04-07', 'Рим'),
		('Национальный музей', '2023-03-07', 'Канберра'),
		('Эрмитаж', '2023-05-03', 'Санкт-Петербург');

INSERT INTO Excursion_in_Trip(excursion_name, trip_number, city_name_in_excursion) VALUES
		('Белградская крепость', 4, 'Белград'),
		('Белый дом', 4, 'Вашингтон'),
		('Белый дом', 5, 'Вашингтон'),
		('Исаакиевская колоннада', 1, 'Санкт-Петербург'),
		('Колизей', 1, 'Рим'),
		('Национальный музей', 2, 'Канберра'),
		('Национальный музей', 3, 'Канберра'),
		('Эрмитаж', 4, 'Санкт-Петербург'),
		('Эрмитаж', 5, 'Санкт-Петербург');

INSERT INTO Room_type(name, city_name_of_hotel, hotel_name) VALUES
		('Люкс', 'Вашингтон', 'Duo housing'),
		('Люкс', 'Канберра', 'The Villiage'),
		('Люкс', 'Рим', 'Сан-Марина'),
		('Люкс', 'Санкт-Петербург', 'Астория'),
		('Президентский', 'Санкт-Петербург', 'Астория'),
		('Эконом', 'Белград', 'City hotel'),
		('Эконом', 'Рим', 'Сан-Марина');

INSERT INTO Room_type_in_Trip(trip_number, room_type_name, city_name_of_hotel, hotel_name) VALUES 
		(1, 'Люкс', 'Рим', 'Сан-Марина'),
		(1, 'Люкс', 'Санкт-Петербург', 'Астория'),
		(2, 'Люкс', 'Канберра', 'The Villiage'),
		(3, 'Люкс', 'Канберра', 'The Villiage'),
		(4, 'Люкс', 'Вашингтон', 'Duo housing'),
		(4, 'Люкс', 'Санкт-Петербург', 'Астория'),
		(4, 'Эконом', 'Белград', 'City hotel'),
		(5, 'Люкс', 'Вашингтон', 'Duo housing'),
		(5, 'Люкс', 'Санкт-Петербург', 'Астория'),
		(5, 'Эконом', 'Белград', 'City hotel');