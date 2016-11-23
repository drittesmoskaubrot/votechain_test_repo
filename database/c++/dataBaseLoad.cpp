// File: example_database_load.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "DBWrapper.h"
#include "common.h" 

// Forward declarations
void loadVendorDB(DBWrapper&, std::string&);
void loadInventoryDB(DBWrapper&, std::string&);

// Loads the contents of vendors.txt and inventory.txt into
// Berkeley DB databases. 
int
main(int argc, char *argv[])
{
    // Initialize the path to the database files
    std::string basename("./");
    std::string databaseHome("./");

    // Database names
    std::string vDbName("vendordb.db");
    std::string iDbName("inventorydb.db");

    // Parse the command line arguments here and determine 
    // the location of the flat text files containing the 
    // inventory data here. This step is omitted for clarity.

    //  Identify the full name for our input files, which should
    //  also include some path information.
    std::string inventoryFile = basename + "inventory.txt";
    std::string vendorFile = basename + "vendors.txt";

    try
    {
        // Open all databases.
        DBWrapper inventoryDB(databaseHome, iDbName);
        DBWrapper vendorDB(databaseHome, vDbName);

        // Load the vendor database
        loadVendorDB(vendorDB, vendorFile);

        // Load the inventory database
        loadInventoryDB(inventoryDB, inventoryFile);
    } catch(DbException &e) {
        std::cerr << "Error loading databases. " << std::endl;
        std::cerr << e.what() << std::endl;
        return(e.get_errno());
    } catch(std::exception &e) {
        std::cerr << "Error loading databases. " << std::endl;
        std::cerr << e.what() << std::endl;
        return(-1);
    }

    return(0);
} // End main 
// Loads the contents of the vendors.txt file into a database
void
loadVendorDB(DBWrapper &vendorDB, std::string &vendorFile)
{
    std::ifstream inFile(vendorFile.c_str(), std::ios::in);
    if ( !inFile )
    {
        std::cerr << "Could not open file '" << vendorFile
                  << "'. Giving up." << std::endl;
        throw std::exception();
    }

    VENDOR my_vendor;
    while (!inFile.eof())
    {
        std::string stringBuf;
        std::getline(inFile, stringBuf);
        memset(&my_vendor, 0, sizeof(VENDOR));

        // Scan the line into the structure.
        // Convenient, but not particularly safe.
        // In a real program, there would be a lot more
        // defensive code here.
        sscanf(stringBuf.c_str(),
          "%20[^#]#%20[^#]#%20[^#]#%3[^#]#%6[^#]#%13[^#]#%20[^#]#%20[^\n]",
          my_vendor.name, my_vendor.street,
          my_vendor.city, my_vendor.state,
          my_vendor.zipcode, my_vendor.phone_number,
          my_vendor.sales_rep, my_vendor.sales_rep_phone);

        Dbt key(my_vendor.name, strlen(my_vendor.name) + 1);
        Dbt data(&my_vendor, sizeof(VENDOR));

        vendorDB.getDb().put(NULL, &key, &data, 0);
    }
    inFile.close();
} 
// Used to locate the first pound sign (a field delimiter)
// in the input string.
int
getNextPound(std::string &theString, std::string &substring)
{
    int pos = theString.find("#");
    substring.assign(theString, 0, pos);
    theString.assign(theString, pos + 1, theString.size());
    return (pos);
}

// Loads the contents of the inventory.txt file into a database
void
loadInventoryDB(DBWrapper &inventoryDB, std::string &inventoryFile)
{
    InventoryData inventoryData;
    std::string substring;
    int nextPound;

    std::ifstream inFile(inventoryFile.c_str(), std::ios::in);
    if (!inFile)
    {
        std::cerr << "Could not open file '" << inventoryFile
                  << "'. Giving up." << std::endl;
        throw std::exception();
    }

    while (!inFile.eof())
    {
        inventoryData.clear();
        std::string stringBuf;
        std::getline(inFile, stringBuf);

        // Now parse the line
        if (!stringBuf.empty())
        {
            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setName(substring);

            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setSKU(substring);

            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setPrice(strtod(substring.c_str(), 0));

            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setQuantity(strtol(substring.c_str(), 0, 10));

            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setCategory(substring);

            nextPound = getNextPound(stringBuf, substring);
            inventoryData.setVendor(substring);

            void *buff = (void *)inventoryData.getSKU().c_str();
            int size = inventoryData.getSKU().size()+1;
            Dbt key(buff, size);

            buff = inventoryData.getBuffer();
            size = inventoryData.getBufferSize();
            Dbt data(buff, size);

            inventoryDB.getDb().put(NULL, &key, &data, 0);
        }
    }
    inFile.close();
} 