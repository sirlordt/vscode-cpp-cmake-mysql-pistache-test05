#include <iostream>

#define MYSQLPP_MYSQL_HEADERS_BURIED 1 //Accept headers with mysql/mysql.h, used in mysqlpp/common.h

#include <mysql/mysql.h>
#include <mysqlpp/mysql++.h>
#include <pistache/endpoint.h>

using namespace Pistache;

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//#include <sqlite3.h>

//From external_libs folder in the root of the project
#include "a1.h"
#include "a2.h"
#include "b1.h"
#include "b2.h"

#include "module_a1.h"
#include "module_a2.h"
#include "module_b1.h"
#include "module_b2.h"

void finish_with_error( MYSQL *con ) {

  fprintf( stderr,
           "%s\n",
           mysql_error( con ) );

  mysql_close( con );

  exit( 1 );

}

// Insert a bar into the stream with the given query string centered
static void separator(ostream& os, string qstr) {
	string sep("========================================"
			"========================================");
	if (qstr.size()) {
		string::size_type start = (sep.size() - qstr.size()) / 2;
		sep.replace(start - 1, 1, 1, ' ');
		sep.replace(start, qstr.size(), qstr);
		sep.replace(start + qstr.size(), 1, 1, ' ');
		os << "\n\n";
	}

	os << sep << endl;

}

// Print out the MySQL server version
static void show_mysql_version(mysqlpp::Connection& con)
{
	separator( cout, "");
  cout << "MySQL version: " << con.client_version();
}


// Print out the names of all the databases managed by the server
static void
show_databases(mysqlpp::Connection& con)
{
	mysqlpp::Query query = con.query("show databases");
	separator(cout, query.str());
	mysqlpp::StoreQueryResult res = query.store();

	cout << "Databases found: " << res.size();
	cout.setf(ios::left);
	mysqlpp::StoreQueryResult::iterator rit;
	for (rit = res.begin(); rit != res.end(); ++rit) {
		cout << "\n\t" << (*rit)[0];
	}
}


// Print information about each of the tables we found
static void
show_table_info(mysqlpp::Connection& con, const vector<string>& tables)
{
	vector<string>::const_iterator it;
	for (it = tables.begin(); it != tables.end(); ++it) {
		mysqlpp::Query query = con.query();
		query << "describe " << *it;
		separator(cout, query.str());
		mysqlpp::StoreQueryResult res = query.store();

		size_t columns = res.num_fields();
		vector<size_t> widths;
		for (size_t i = 0; i < columns; ++i) {
			string s = res.field_name(int(i));
			if (s.compare("field") == 0) {
				widths.push_back(22);
			}
			else if (s.compare("type") == 0) {
				widths.push_back(20);
			}
			else if (s.compare("null") == 0) {
				widths.push_back(4);
			}
			else if (s.compare("key") == 0) {
				widths.push_back(3);
			}
			else if (s.compare("extra") == 0) {
				widths.push_back(0);
			}
			else {
				widths.push_back(15);
			}

			if (widths[i]) {
				cout << '|' << setw(widths[i]) << 
						res.field_name(int(i)) << '|';
			}
		}
		cout << endl;

		mysqlpp::StoreQueryResult::iterator rit;
		for (rit = res.begin(); rit != res.end(); ++rit) {
			for (unsigned int i = 0; i < columns; ++i) {
				if (widths[i]) {
					cout << ' ' << setw(widths[i]) <<
							(*rit)[i].c_str() << ' ';
				}
			}
			cout << endl;
		}
	}
}

// Print out the names of all tables in the sample database, and
// return the list of tables.
static void
show_tables(mysqlpp::Connection& con)
{
	mysqlpp::Query query = con.query("show tables");
	separator(cout, query.str());
	mysqlpp::StoreQueryResult res = query.store();

	cout << "Tables found: " << res.size();
	cout.setf(ios::left);
	vector<string> tables;
	mysqlpp::StoreQueryResult::iterator rit;
	for (rit = res.begin(); rit != res.end(); ++rit) {
		string tbl((*rit)[0]);
		cout << "\n\t" << tbl;
		tables.push_back(tbl);
	}

	show_table_info(con, tables);
}

class HelloHandler : public Http::Handler
{
public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& /*request*/, Http::ResponseWriter response) override
    {
        response.send(Pistache::Http::Code::Ok, "Hello World\n");
    }
};

int main( int argc, char **argv ) {

  std::cout << "Hello from main" << std::endl; 

  std::cout << getExternalLibA1( "Tomas1" ) << std::endl;
  std::cout << getExternalLibA2( "Tomas2" ) << std::endl;

  std::cout << getExternalLibB1( "Rafael1" ) << std::endl;
  std::cout << getExternalLibB2( "Rafael2" ) << std::endl;

  std::cout << getModuleA1( "Moreno1" ) << std::endl;
  std::cout << getModuleA2( "Moreno2" ) << std::endl;

  std::cout << getModuleB1( "Poggio1" ) << std::endl;
  std::cout << getModuleB2( "Poggio2" ) << std::endl;

  A1 a1 = A1();

  a1.a1Method();

  //std::cout <<  "SQLite Version: " << sqlite3_libversion() << std::endl;

  try {

    mysqlpp::Connection con1( "TestDB",
                              "localhost",
                              "root",
                              "dsistemas" );

    show_mysql_version( con1 );
    show_databases( con1 );
    show_tables( con1 );

  }
  catch ( const mysqlpp::BadQuery& error ) {

	// Handle any query errors
    cerr << "Query error: " << error.what() << endl;
	return -1;

  }
  catch ( const mysqlpp::Exception& error ) {

	// Catch-all for any other MySQL++ exceptions
	cerr << "Error: " << error.what() << endl;
	return -1;

  }

  MYSQL *con = mysql_init( NULL );

  if ( mysql_real_connect( con,
                           "localhost",
                           "root",
                           "dsistemas",
                           "TestDB",
                           0,
                           NULL,
                           0 ) == NULL ) {
    
    finish_with_error( con );

  }

  if ( mysql_query( con, "CREATE TABLE IF NOT EXISTS cars(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Audi',52642)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Mercedes',57127)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Skoda',9000)" ) ) {
    
    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Volvo',29000)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Bentley',350000)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Citroen',21000)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Hummer',41400)" ) ) {

    finish_with_error( con );

  }

  if ( mysql_query( con, "INSERT INTO cars( name, price ) VALUES('Volkswagen',21600)" ) ) {
    
    finish_with_error( con );

  }

  mysql_close( con );

  //std::string key;

  std::cout << "Wainting for enter" << std::endl;
  std::cin.get(); // >> key;

  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
  auto opts = Pistache::Http::Endpoint::options().threads(1);

  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(Http::make_handler<HelloHandler>());

  std::cout << "Server listening in port 9080" << std::endl;
  server.serve();

  return 0;

} 