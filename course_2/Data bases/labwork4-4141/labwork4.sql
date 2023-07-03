-- Лабораторная работа №4, дисциплина "Базы данных", СПбГУАП, весенний семестр 2023

-- Удаление представлений
DROP VIEW IF EXISTS international_routes_stations_count_in_cities;
DROP VIEW IF EXISTS Clients_travelling_alone_and_stay_in_lux;
DROP VIEW IF EXISTS Clients_with_different_routes_and_only_country_without_excursions;

-- Создание представлений
-- 1) Клиенты, которые ездили за последний год в несколько поездок по разным маршрутам, но всегда только по одной стране, и ни разу не заказывавшие экскурсии
CREATE VIEW Clients_with_different_routes_and_only_country_without_excursions AS
SELECT DISTINCT full_name
FROM Trip, Tourist_group, Station, City, Client
WHERE Trip.group_number = Tourist_group.group_number
      AND Tourist_group.route_name = Station.route_name
      AND Trip.clients_phone_number = Client.phone_number
      AND City.name = Station.city_name
      AND travel_date > DATETIME('NOW', 'LOCALTIME', '-1 YEAR')
      AND travel_date <= DATETIME('NOW', 'LOCALTIME')
      AND Trip.clients_phone_number NOT IN (
	      -- проверяем отсутсвие экскурсий
          SELECT DISTINCT clients_phone_number
          FROM Excursion_in_Trip, Trip
          WHERE Excursion_in_Trip.trip_number = Trip.trip_number
       )
GROUP BY full_name
HAVING COUNT(DISTINCT country_name) = 1 AND COUNT (DISTINCT Tourist_group.route_name) > 1;

-- 2) Для каждого города подсчитать, сколько международных маршрутов останавливается в нем более чем на день
CREATE VIEW international_routes_stations_count_in_cities AS
SELECT COUNT(DISTINCT route_name) as international_station_count, city_name
FROM Station
WHERE duration > 1 
      AND route_name IN (
       SELECT route_name
       FROM Station a, City b
       WHERE b.name = a.city_name
       GROUP BY a.route_name
       HAVING COUNT(DISTINCT b.country_name) > 1
      )
GROUP BY city_name;

-- 3) Клиенты, которые всегда ездят в одиночку и останавливаются только в номерах "Люкс"
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

-- Оператор UPDATE
-- Уменьшить стоимость маршрутов, у которых хотя бы раз за последний год не набралась полная группа
UPDATE Route
SET price = price * 0.75
WHERE Route.name in (
      SELECT route_name
      FROM Tourist_group, Route, Trip
      WHERE Route.name = Tourist_group.route_name
            AND Tourist_group.group_number = Trip.group_number
            AND Route.start_date > DATETIME('NOW', 'LOCALTIME', '-1 YEAR')
            AND Route.start_date <= DATETIME('NOW', 'LOCALTIME')
      GROUP BY Tourist_group.group_number
      HAVING COUNT(DISTINCT clients_phone_number) < max_count
  );

-- Оператор DELETE
-- Удалить экскурсии, которые никто никогда не заказывал
DELETE FROM Excursion
WHERE Excursion.name NOT IN (
      SELECT DISTINCT Excursion_in_Trip.excursion_name
      FROM Excursion_in_Trip
);