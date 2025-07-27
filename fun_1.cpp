class DB {
    class DBInit {
    public:
        DBInit() = default;
        
        DBInit& SetName(string_view db_name){
            db_name_ = db_name;
        }
        DBInit& SetConnectionTimeout(int db_connection_timeout){
            db_connection_timeout_ = db_connection_timeout;
        }
        DBInit& SetAllowExceptions(bool db_allow_exceptions){
            db_allow_exceptions_ = db_allow_exceptions;
        }
        DBInit& SetLogLevel(DBLogLevel db_log_level){
            db_log_level_ = db_log_level;
        }
        
        operator DB() const {
            return {db_name_, db_connection_timeout_, db_allow_exceptions_, db_log_level_};
        }
        
    private:
        string_view db_name_;
        int db_connection_timeout_;
        bool db_allow_exceptions_;
        DBLogLevel db_log_level_;
    };  //... DBInit ...............................................
    
    
    vector<Person> LoadPersons(int min_age, int max_age, string_view name_filter) {
        if (!db_allow_exceptions && !db.IsOK()) {
            return {};
        }
        
        DBQuery query( CreateQueryStr(min_age, max_age, name_filter).str() );
        vector<Person> persons;
        for (auto [name, age] : db.LoadRows<string, int>(query)) {
            persons.push_back({move(name), age});
        }
        return persons;
    }
    
    
private:
    DB(string_view db_name, int db_connection_timeout, bool db_allow_exceptions, DBLogLevel db_log_level)
        : db_name_(db_name)
        , db_connection_timeout_(db_connection_timeout)
        , connector(db_allow_exceptions, db_log_level) {
        
        if (db_name.starts_with("tmp."s)) {
            db = connector.ConnectTmp(db_name, db_connection_timeout);
        } else {
            db = connector.Connect(db_name, db_connection_timeout);
        }
    }
    
    ostringstream CreateQueryStr(int min_age, int max_age, string_view name_filter) {
        ostringstream query_str;
        query_str << "from Persons "s
                  << "select Name, Age "s
                  << "where Age between "s << min_age << " and "s << max_age << " "s
                  << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
        return query_str;
    }
    
    string_view db_name_;
    int db_connection_timeout_;
    bool db_allow_exceptions_;
    DBLogLevel db_log_level_;
    
    DBConnector connector;
    DBHandler db;
    
};


int main(){
    DB db_create(DB::DBInit().SetName("funtik"s).SetConnectionTimeout(12).SetAllowExceptions(true).SetLogLevel(DBLogLevel{}) );
    vector<Person> vec_person = db_create.LoadPersons(45, 56, "fff"s);
}



