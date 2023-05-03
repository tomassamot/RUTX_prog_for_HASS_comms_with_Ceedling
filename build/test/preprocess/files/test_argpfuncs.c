#include "src/ll_module.h"
#include "src/argpfuncs.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


#define TEST_CASE(...) 





struct arguments arguments = { {[0 ... 19] = '\0'}, 0, {[0 ... 49] = '\0'}, {[0 ... 49] = '\0'}, 0, .pub_modules=NULL, .sub_modules=NULL};



void setUp(void)

{

    arguments.broker_address[0] = '\0';

    arguments.broker_port = 0;

    arguments.username[0] = '\0';

    arguments.password[0] = '\0';

    arguments.pub_modules = NULL;

    arguments.sub_modules = NULL;

}

void tearDown(void)

{

}





// void test_ShouldParseEverything(void)

// {

//     char expected[20] = "192.168.1.249", actual[20];

//     int argc = 12;

//     char *argv[] = {"prog_for_mint", "-D", "-a", "192.168.1.249", "-p", "1883", "-U", "broker" "-P", "brokerpass" "-b", "mint-ip,mint-ram,mint-wireless", "-s", "mint-ban_device"};



//     start_parser(argc, argv, &arguments);

//     TEST_ASSERT_MESSAGE(NULL != arguments.broker_address, "Broker address shouldn't be NULL after parse");

//     strcpy(actual, arguments.broker_address);



//     TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, "Unexpected broker address after parse");

// }

void test_ShouldParseBrokerAddressAndPort(void)

{

    char expected_address[20] = "192.168.1.249", actual_address[20];

    int expected_port = 1883, actual_port = 0;

    int argc = 5;

    char *argv[] = {"prog_for_mint", "-a", "192.168.1.249", "-p", "1883"};





    start_parser(argc, argv, &arguments);

    strcpy(actual_address, arguments.broker_address);

    actual_port = arguments.broker_port;

    



    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_address, actual_address, "Unexpected broker address after parse");

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_port, actual_port, "Unexpected broker port after parse");

}

void test_ShouldParseUsernameAndPassword(void)

{

    char expected_username[50] = "broker", actual_username[50], expected_password[50]="brokerpass", actual_password[50];

    int argc = 9;

    char *argv[] = {"prog_for_mint", "-a", "192.168.1.249", "-p", "1883", "-U", "broker", "-P", "brokerpass"};





    start_parser(argc, argv, &arguments);

    strcpy(actual_username, arguments.username);

    strcpy(actual_password, arguments.password);

    



    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_username, actual_username, "Unexpected username after parse");

    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_password, actual_password, "Unexpected password port after parse");

}



void test_ShouldParsePubModules(void)

{

    int argc = 7;

    char *argv[] = {"prog_for_mint", "-a", "192.168.1.249", "-p", "1883", "b", "mint-pubmod1,mint-pubmod2"};

    struct ll_module *expected_pub_modules = NULL, *actual_pub_modules = NULL;

    ll_module_add(&expected_pub_modules, ll_module_create("mint-pubmod1"));

    ll_module_add(&expected_pub_modules, ll_module_create("mint-pubmod2"));





    start_parser(argc, argv, &arguments);

    actual_pub_modules = arguments.pub_modules;

    



    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_pub_modules->name, actual_pub_modules->name, "Unexpected first pub module name after parse");

    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_pub_modules->next->name, actual_pub_modules->next->name, "Unexpected second pub module name after parse");

}

// #endif // TEST
