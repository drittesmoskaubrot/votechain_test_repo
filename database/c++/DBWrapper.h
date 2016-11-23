#include <db_cxx.h>

class DBWrapper
{
public:
    // Constructor requires a path to the database,
    // and a database name.
    DBWrapper(std::string &path, std::string &dbName);

    // Our destructor just calls our private close method.
    ~DBWrapper() { close(); }

    inline Db &getDb() {return db_;}

private:
    Db db_;
    std::string dbFileName_;
    u_int32_t cFlags_;

    // Make sure the default constructor is private
    // We don't want it used.
    DBWrapper() : db_(NULL, 0) {}

    // We put our database close activity here.
    // This is called from our destructor. In
    // a more complicated example, we might want
    // to make this method public, but a private
    // method is more appropriate for this example.
    void close();
}; 


