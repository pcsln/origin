#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>
#include <iomanip>

class Person {
private:
	std::string str_host = "host=localhost ";
	std::string str_port = "port=5432 ";
	std::string str_dbname = "dbname=postgres ";
	std::string str_user = "user=postgres ";
	std::string str_pass = "password=20miami4883";

	pqxx::connection connection = pqxx::connection(get_connection_string());
public:
	
	std::string get_connection_string() {
		return str_host + str_port + str_dbname + str_user + str_pass;
	}

	Person() {
		
 	}
	
	void create_tables() {
		pqxx::transaction tx{ connection };

		tx.exec("CREATE TABLE IF NOT EXISTS Person ( "
				"id SERIAL PRIMARY KEY, "
				"name VARCHAR(60) NOT NULL, "
				"surname VARCHAR(60) NOT NULL, "
				"email VARCHAR(60) NOT NULL); ");

		tx.exec("CREATE TABLE IF NOT EXISTS Phone ( "
			"id SERIAL PRIMARY KEY, "
			"number VARCHAR(60), "
			"person_id INTEGER REFERENCES Person(id)); ");

		tx.commit();
	}

	void add_phone(std::string name, std::string surname, std::string email, std::string phone) {
		pqxx::transaction tx{ connection };
		
		std::string query = "INSERT INTO phone(person_id, number) VALUES( "
			"(SELECT id FROM person WHERE "
			"name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
			"AND email = \'" + tx.esc(email) + "\'),\'" + tx.esc(phone) + "\'); ";

		tx.exec(query);

		tx.commit();
	}

	void insert_person(std::string name, std::string surname, std::string email) {
		pqxx::transaction tx{ connection };

		std::string query = "INSERT INTO person(name, surname, email) "
							" VALUES(\'" + tx.esc(name) + "\',\'" + tx.esc(surname) + "\',\'" + tx.esc(email) + "\');";

		tx.exec(query);

		tx.commit();
	}

	void insert_person(std::string name, std::string surname, std::string email, std::string phone) {
		pqxx::transaction tx{ connection };
		
		std::string query = "INSERT INTO person(name, surname, email) "
							"VALUES(\'" + tx.esc(name) + "\',\'" + tx.esc(surname) + "\',\'" + tx.esc(email) + "\');";
		
		tx.exec(query);

		tx.commit();

		add_phone(name, surname, email, phone);
	}

	void update_name(std::string name, std::string surname, std::string email, std::string new_name) {
		pqxx::transaction tx{ connection };

		std::string query = "UPDATE person SET name = \'" + tx.esc(new_name) + "\' "
							"WHERE name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
							"AND email = \'" + tx.esc(email) + "\';";

		tx.exec(query);

		tx.commit();
	}

	void update_surname(std::string name, std::string surname, std::string email, std::string new_surname) {
		pqxx::transaction tx{ connection };

		std::string query = "UPDATE person SET surname = \'" + tx.esc(new_surname) + "\' "
							"WHERE name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
							"AND email = \'" + tx.esc(email) + "\';";

		tx.exec(query);

		tx.commit();
	}

	void update_email(std::string name, std::string surname, std::string email, std::string new_email) {
		pqxx::transaction tx{ connection };

		std::string query = "UPDATE person SET email = \'" + tx.esc(new_email) + "\' "
							"WHERE name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
							"AND email = \'" + tx.esc(email) + "\';";

		tx.exec(query);

		tx.commit();
	}

	void delete_phone(std::string name, std::string surname, std::string email) {
		pqxx::transaction tx{ connection };

		std::string query = "DELETE FROM phone WHERE person_id = "
							"(SELECT id FROM person "
							"WHERE name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
							"AND email = \'" + tx.esc(email) + "\');";

		tx.exec(query);

		tx.commit();
	}

	void delete_person(std::string name, std::string surname, std::string email) {
		
		delete_phone(name, surname, email);

		pqxx::transaction tx{ connection };

		std::string query = "DELETE FROM person "
							"WHERE name=\'" + tx.esc(name) + "\' AND surname=\'" + tx.esc(surname) + "\' "
							"AND email = \'" + tx.esc(email) + "\';";

		tx.exec(query);

		tx.commit();
	}

	void select_by_name(std::string name) {
		pqxx::transaction tx{ connection };

		std::string query = "SELECT p.id, name, surname, email, "
							"(CASE WHEN ph.number IS NOT NULL THEN ph.number ELSE \'\' END) FROM person p "
							"LEFT JOIN phone ph ON p.id=ph.person_id WHERE p.name=\'" + tx.esc(name) +"\' ;";

		pqxx::result result = tx.exec(query);

		if (result.size() == 0) {
			std::cout << "Not found." << std::endl;
		}

		int i = 1;
		for (pqxx::result::const_iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << std::setw(3) << i++;
			std::cout << std::setw(15) << it[1].as<std::string>();
			std::cout << std::setw(15) << it[2].as<std::string>();
			std::cout << std::setw(20) << it[3].as<std::string>();
			std::cout << std::setw(15) << it[4].as<std::string>();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void select_by_surname(std::string surname) {
		pqxx::transaction tx{ connection };

		std::string query = "SELECT p.id, name, surname, email, "
			"(CASE WHEN ph.number IS NOT NULL THEN ph.number ELSE \'\' END) FROM person p "
			"LEFT JOIN phone ph ON p.id=ph.person_id WHERE p.surname=\'" + tx.esc(surname) + "\' ;";

		pqxx::result result = tx.exec(query);

		if (result.size() == 0) {
			std::cout << "Not found." << std::endl;
		}

		int i = 1;
		for (pqxx::result::const_iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << std::setw(3) << i++;
			std::cout << std::setw(15) << it[1].as<std::string>();
			std::cout << std::setw(15) << it[2].as<std::string>();
			std::cout << std::setw(20) << it[3].as<std::string>();
			std::cout << std::setw(15) << it[4].as<std::string>();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void select_by_email(std::string email) {
		pqxx::transaction tx{ connection };

		std::string query = "SELECT p.id, name, surname, email, "
			"(CASE WHEN ph.number IS NOT NULL THEN ph.number ELSE \'\' END) FROM person p "
			"LEFT JOIN phone ph ON p.id=ph.person_id WHERE p.email=\'" + tx.esc(email) + "\' ;";

		pqxx::result result = tx.exec(query);

		if (result.size() == 0) {
			std::cout << "Not found. << std::endl";
		}

		int i = 1;
		for (pqxx::result::const_iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << std::setw(3) << i++;
			std::cout << std::setw(15) << it[1].as<std::string>();
			std::cout << std::setw(15) << it[2].as<std::string>();
			std::cout << std::setw(20) << it[3].as<std::string>();
			std::cout << std::setw(15) << it[4].as<std::string>();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void select_by_phone(std::string phone) {
		pqxx::transaction tx{ connection };

		std::string query = "SELECT p.id, name, surname, email, "
			"(CASE WHEN ph.number IS NOT NULL THEN ph.number ELSE \'\' END) FROM person p "
			"LEFT JOIN phone ph ON p.id=ph.person_id WHERE ph.number=\'" + tx.esc(phone) + "\' ;";

		pqxx::result result = tx.exec(query);

		if (result.size() == 0) {
			std::cout << "Not found. << std::endl";
		}

		int i = 1;
		for (pqxx::result::const_iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << std::setw(3) << i++;
			std::cout << std::setw(15) << it[1].as<std::string>();
			std::cout << std::setw(15) << it[2].as<std::string>();
			std::cout << std::setw(20) << it[3].as<std::string>();
			std::cout << std::setw(15) << it[4].as<std::string>();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void select_all() {
		pqxx::transaction tx{ connection };

		std::string query = "SELECT p.id, name, surname, email, "
			"(CASE WHEN ph.number IS NOT NULL THEN ph.number ELSE \'\' END) FROM person p "
			"LEFT JOIN phone ph ON p.id=ph.person_id ORDER BY name;";
		
		pqxx::result result = tx.exec(query);



		int i = 1;
		for (pqxx::result::const_iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << std::setw(3) << i++;
			std::cout << std::setw(15) << it[1].as<std::string>();
			std::cout << std::setw(15) << it[2].as<std::string>();
			std::cout << std::setw(20) << it[3].as<std::string>();
			std::cout << std::setw(15) << it[4].as<std::string>();
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

};

int main() {

	
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		Person person;
		person.create_tables();
		
		// Добавление в базу персон с телефоном
		
		person.insert_person("Alex", "Rodin", "rodin@mail.ru", "+79272325810");
		person.insert_person("Maximilian", "Rodin", "max@mail.ru", "+79272325811");
		person.insert_person("James", "Cooper", "cooper@mail.ru", "+70007864544");
		person.insert_person("Ditrich", "Swartzkopf", "ds@mail.ru", "+78908908900");
		person.insert_person("Anna", "Chavari", "cavva@mail.ru", "+745609090909");
		person.insert_person("Bebila", "Cann", "bebican@mail.ru", "+73330005649");
		person.insert_person("Lolita", "Kamalova", "lola@mail.ru", "+72322728052");
		
		// Добавление в базу персон без телефона
		
		person.insert_person("Cristian", "Sowl", "sc_2017@mail.ru");
		person.insert_person("Alina", "Cooc", "alina@mail.ru");
		person.insert_person("Miguel", "Chendo", "chendodo@mail.ru");

		// Вывод на экран всех добавленных

		person.select_all();

		// Добавление телефонов

		person.add_phone("James", "Cooper", "cooper@mail.ru", "+79994560102");
		person.add_phone("Alina", "Cooc", "alina@mail.ru", "+78881120911");

		// Изменение имени

		person.update_name("Alex", "Rodin", "rodin@mail.ru", "Alexander");

		// Изменение фамилии
		
		person.update_surname("Maximilian", "Rodin", "max@mail.ru", "Bittner");
		
		// Изменение email

		person.update_email("Cristian", "Sowl", "sc_2017@mail.ru", "cristian@bk.ru");
		
		// Удаление телефона
		
		person.delete_phone("Bebila", "Cann", "bebican@mail.ru");

		// Удаление персоны 
		
		person.delete_person("Lolita", "Kamalova", "lola@mail.ru");
		
		// Поиск по имени 
		
		person.select_by_name("James");

		// Поиск по фамилии
		
		person.select_by_surname("Cooper");

		// Поиск по email

		person.select_by_email("ds@mail.ru");

		// Поиск по телефону

		person.select_by_phone("+78881120911");

		// Вывод на экран
		
		person.select_all();
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}




}