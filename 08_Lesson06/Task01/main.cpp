#include <iostream>
#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Windows.h>

using namespace Wt::Dbo;


class Book;
class Stock;
class Sale;

class Publisher {
public:
	std::string name;
	collection<ptr<Book>> books;

	template<typename Action>
	void persist(Action a) {
		field(a, name, "name");
		hasMany(a, books, ManyToOne, "publisher");
	}
};

class Book {
public:
	std::string title;
	ptr<Publisher> publisher;
	collection<ptr<Stock>> stocks;

	template<typename Action>
	void persist(Action a) {
		field(a, title, "title");
		belongsTo(a, publisher, "publisher");
		hasMany(a, stocks, ManyToOne, "book");
	}
};

class Shop {
public:
	std::string name;
	collection<ptr<Stock>> stocks;

	template<typename Action>
	void persist(Action a) {
		field(a, name, "name");
		hasMany(a, stocks, ManyToOne, "shop");
	}
};

class Stock {
public:
	int count;
	ptr<Book> book;
	ptr<Shop> shop;
	collection<ptr<Sale>> sales;

	template<typename Action> 
	void persist(Action& a) {
		field(a, count, "count");
		belongsTo(a, book, "book");
		belongsTo(a, shop, "shop");
		hasMany(a, sales, ManyToOne, "stock");
	}
};

class Sale {
public:
	int count;
	int price;
	std::string date_sale;
	ptr<Stock> stock;

	template<typename Action>
	void persist(Action& a) {
		field(a, count, "count");
		field(a, price, "price");
		field(a, date_sale, "date_sale");
		belongsTo(a, stock, "stock");
	}
};

class Trader {
private:
public:
	std::unique_ptr<backend::Postgres> connection;
	std::string connection_string = "host=localhost "
									"port=5432 "
									"dbname=postgres "
									"user=postgres "
									"password=20miami4883";
	Session session;

	Trader() {

		std::string connectionString(connection_string);

		connection = std::make_unique<backend::Postgres>(connectionString);

		session.setConnection(std::move(connection));

		session.mapClass<Publisher>("publisher");
		session.mapClass<Shop>("shop");
		session.mapClass<Book>("book");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");
	}

	void create_tables() {
		session.createTables();
	}

	ptr<Publisher> add_publisher(std::string publisher_name) {
		Transaction tx{ session };

		std::unique_ptr<Publisher> publisher{ new Publisher {publisher_name, {}} };
		
		auto publisher_ptr = session.add(move(publisher));

		tx.commit();

		return publisher_ptr;
	}

	ptr<Shop> add_shop(std::string shop_name) {
		Transaction tx{ session };

		std::unique_ptr<Shop> shop{ new Shop {shop_name, {}} };

		auto shop_ptr = session.add(move(shop));

		tx.commit();

		return shop_ptr;
	}

	ptr<Book> add_book(std::string title) {
		Transaction tx{ session };

		std::unique_ptr<Book> book{ new Book {title, {}, {} } };

		auto book_ptr = session.add(move(book));

		tx.commit();

		return book_ptr;
	}


	ptr<Publisher> find_publisher(std::string name) {
		Transaction tx{ session };
		ptr<Publisher> p = session.find<Publisher>().where("name = ?").bind(name);
		tx.commit();
		return p;
	}

	ptr<Shop> find_shop(std::string name) {
		Transaction tx{ session };
		ptr<Shop> s = session.find<Shop>().where("name = ?").bind(name);
		tx.commit();
		return s;
	}

	ptr<Book> find_book(std::string title) {
		Transaction tx{ session };
		ptr<Book> b = session.find<Book>().where("title = ?").bind(title);
		tx.commit();
		return b;
	}



	void add_book_publisher(std::string book_title, std::string publisher_name) {
		try {
			if (find_publisher(publisher_name)) {
				Transaction tx{ session };
				add_book(book_title).modify()->publisher = session.find<Publisher>().where("name = ?").bind(publisher_name);
				tx.commit();
			}
			else {
				Transaction tx{ session };
				add_book(book_title).modify()->publisher = add_publisher(publisher_name);
				tx.commit();
			}
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
	}

	ptr<Stock> add_stock_to_shop(int count, std::string title, std::string shop_name) {
		
			Transaction tx{ session };

			std::unique_ptr<Stock> stock{ new Stock {count, {}, {} } };

			
			ptr<Stock> stock_ptr = session.add(move(stock));

			if (find_book(title)) {
				stock_ptr.modify()->book = session.find<Book>().where("title = ?").bind(title);
			}
			else {
				stock_ptr.modify()->book = add_book(title);
			}
			
			if (find_shop(shop_name)) {
				stock_ptr.modify()->shop = session.find<Shop>().where("name = ?").bind(shop_name);
			}
			else {
				stock_ptr.modify()->shop = add_shop(shop_name);
			}

			tx.commit();

		return stock_ptr;
	}

	void sales(int count, int price, std::string date, ptr<Stock>& stock) {
		Transaction tx{ session };

		std::unique_ptr<Sale> sale{ new Sale {count, price, date, stock} };
		session.add(move(sale));


		tx.commit();
	}

	void find_shops(int id) {
		
		typedef collection<ptr<Book>> Books;
		typedef collection<ptr<Stock>> Stocks;
		typedef collection<ptr<Shop>> Shops;
		
		Transaction tx{ session };
		Books books = session.find<Book>().where("publisher_id=?").bind(id);

		
		
		for (const ptr<Book>& book : books)
		{
			Stocks stocks = session.find<Stock>().where("book_id = ?").bind(book);		
			for (const ptr<Stock>& stock : stocks)
			{	
				Shops shops = session.find<Shop>().where("id = ?").bind(stock->shop);
				for (const ptr<Shop>& shop : shops) {

					std::cout << "\"" << book->title << "\"" << " in the shop \"" << shop->name << "\"" << std::endl;
				}
			}
		}
		tx.commit();
	}

	void find_shops_by_publishers() {
		
		std::cout << "Select the publisher id:" << std::endl << std::endl;

		typedef collection<ptr<Publisher>> Publishers;

		Transaction tx{ session };
		Publishers publishers = session.find<Publisher>();

		for (const ptr<Publisher>& publisher : publishers)
		{
			std::cout << publisher.id() << " " << publisher->name << std::endl;
		}
		tx.commit();

		int select;
		std::cout << std::endl;
		std::cin >> select;
		std::cout << std::endl;
		std::cout << "The books of the selected publishing house are sale:" << std::endl;

		find_shops(select);
	}

	void fill_db() {
		create_tables();

		add_book_publisher("C++", "PITER");
		add_book_publisher("Herding Cats", "PITER");
		add_book_publisher("Launch", "PITER");
		add_book_publisher("Computer Science Distilled", "PITER");

		add_book_publisher("INSPIRED", "MYTH");
		add_book_publisher("Aesthetic Intelligence", "MYTH");
		add_book_publisher("Habits Of A Happy Brain", "MYTH");

		add_book_publisher("New Arabian Nights", "AST");
		add_book_publisher("Martin Eden", "AST");

		add_book_publisher("Logic", "PROSPEKT");

		auto stock01 = add_stock_to_shop(10, "C++", "Azbuka");
		auto stock02 = add_stock_to_shop(20, "Herding Cats", "Rostov");
		auto stock03 = add_stock_to_shop(30, "Launch", "Gorod");
		auto stock04 = add_stock_to_shop(40, "Computer Science Distilled", "Marks");
		auto stock05 = add_stock_to_shop(50, "INSPIRED", "AquaMall");
		auto stock06 = add_stock_to_shop(60, "Aesthetic Intelligence", "Dublin");
		auto stock07 = add_stock_to_shop(70, "Habits Of A Happy Brain", "BookShop");
		auto stock08 = add_stock_to_shop(80, "New Arabian Nights", "Windows");
		auto stock09 = add_stock_to_shop(90, "Martin Eden", "Laika");
		auto stock10 = add_stock_to_shop(100, "Logic", "Versal");
		auto stock11 = add_stock_to_shop(14, "C++", "Versal");
		auto stock12 = add_stock_to_shop(28, "Herding Cats", "Laika");
		auto stock13 = add_stock_to_shop(42, "Launch", "Windows");
		auto stock14 = add_stock_to_shop(56, "Computer Science Distilled", "Leningraf");
		auto stock15 = add_stock_to_shop(60, "INSPIRED", "Dublin");
		auto stock16 = add_stock_to_shop(74, "Aesthetic Intelligence", "AquaMall");
		auto stock17 = add_stock_to_shop(88, "Habits Of A Happy Brain", "Marks");
		auto stock18 = add_stock_to_shop(102, "New Arabian Nights", "Gorod");
		auto stock19 = add_stock_to_shop(116, "Martin Eden", "Rostov");
		auto stock20 = add_stock_to_shop(130, "Logic", "Azbuka");

		sales(1, 1500, "2023-11-18", stock01);
		sales(3, 1500, "2023-11-18", stock02);
		sales(6, 1500, "2023-11-18", stock03);
		sales(9, 1500, "2023-11-18", stock04);
		sales(12, 1500, "2023-11-18", stock05);
		sales(15, 1500, "2023-11-18", stock06);
		sales(18, 1500, "2023-11-18", stock07);
		sales(21, 1500, "2023-11-18", stock08);
		sales(24, 1500, "2023-11-18", stock09);
		sales(27, 1500, "2023-11-18", stock10);
		sales(2, 1500, "2023-11-19", stock01);
		sales(6, 1500, "2023-11-19", stock02);
		sales(10, 1500, "2023-11-19", stock03);
		sales(14, 1500, "2023-11-19", stock04);
		sales(18, 1500, "2023-11-19", stock05);
		sales(22, 1500, "2023-11-19", stock06);
		sales(26, 1500, "2023-11-19", stock07);
		sales(30, 1500, "2023-11-19", stock08);
		sales(34, 1500, "2023-11-19", stock09);
		sales(38, 1500, "2023-11-19", stock10);
	}

};

int main() {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try {
		Trader trader;
		trader.fill_db();

		trader.find_shops_by_publishers();
	}
	catch(const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

}