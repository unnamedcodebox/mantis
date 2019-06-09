#include "../core/Database.h"
#include "../core/IsbQuery.h"
#include <QtXlsx>

#include <QDebug>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <gtest/gtest.h>

using namespace mantis;

TEST(readDatabaseConfigFromFile, Positive)
{
    using namespace mantis;
    boost::property_tree::ptree config;
    boost::property_tree::read_json("config.json", config);
    EXPECT_EQ(std::string{"QPSQL"}, config.get<std::string>("driver"));
    EXPECT_EQ(std::string{"127.0.0.1"}, config.get<std::string>("hostaddr"));
    EXPECT_EQ(std::string{"SBAJournal"}, config.get<std::string>("dbname"));
    EXPECT_EQ(std::string{"phpuser"}, config.get<std::string>("username"));
    boost::optional<boost::property_tree::ptree&> pass
        = config.get_child_optional("password");
    if (pass)
    {
        EXPECT_EQ(std::string{ "" }, config.get<std::string>("password"));
    }
}

TEST(createDatabaseFromConfig, Positive)
{
    using namespace mantis;
    boost::property_tree::ptree config;
    boost::property_tree::read_json("config.json", config);
    auto database = Database(config);
    auto query = IsbQuery(AppName::PCS, "01/03/2019", "01/04/2019");
}
