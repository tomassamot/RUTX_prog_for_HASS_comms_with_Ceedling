// #ifdef TEST

#include "unity.h"
#include "ll_module.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#define TEST_CASE(...)


struct ll_module *list;

void setUp(void)
{
    list = NULL;
}

void tearDown(void)
{
    ll_module_deallocate(&list);
}

void fill_modules_list(int modules_amount)
{
    int i = 0;
    while(i < modules_amount){
        char name[20];
        sprintf(name, "mint-mod%d", i);

        ll_module_add(&list, ll_module_create(name));
        i++;
    }
}
void fill_given_modules_list(struct ll_module **given_list, int modules_amount)
{
    int i = 0;
    while(i < modules_amount){
        char name[20];
        sprintf(name, "mint-mod%d", i);

        ll_module_add(given_list, ll_module_create(name));
        i++;
    }
}



void test_ShouldCreateNewModuleWithNameSuccessfully(void)
{

    list = ll_module_create("mint-mod1");


    TEST_ASSERT_EQUAL_STRING_MESSAGE("mint-mod1", list->name, "Expected moudle's name and created actual module's name do not match");
}
void test_ShouldAddOneNewModuleToEmptyList(void)
{
    struct ll_module *mod1 = ll_module_create("mint-mod1");


    ll_module_add(&list, mod1);


    TEST_ASSERT_MESSAGE(NULL == list->next, "Unexpected more than one module in list");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(mod1->name, list->name, "Unexpected module's name in list");
}
void test_ShouldAddTwoNewModulesToEmptyList(void)
{
    struct ll_module *mod1 = ll_module_create("mint-mod1"), *mod2 = ll_module_create("mint-mod2");


    ll_module_add(&list, mod1);
    ll_module_add(&list, mod2);


    TEST_ASSERT_MESSAGE(NULL != list->next, "Expected more than one module in list");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(mod1->name, list->name, "Unexpected first module's name in list");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(mod2->name, list->next->name, "Unexpected second module's name in list");
}
void test_ShouldNotAddOneNullModuleToEmptyList(void)
{
    struct ll_module *mod1 = NULL;


    ll_module_add(&list, mod1);


    TEST_ASSERT_MESSAGE(NULL == list, "Expected list to be empty");
}
void test_ShouldNotAddTwoNullModulesToEmptyList(void)
{
    struct ll_module *mod1 = NULL, *mod2 = NULL;


    ll_module_add(&list, mod1);
    ll_module_add(&list, mod2);


    TEST_ASSERT_MESSAGE(NULL == list, "Expected list to be empty");
}
void test_ShouldAddEachModuleInListToEmptyList(void)
{
    struct ll_module *new_list = NULL;
    fill_given_modules_list(&new_list, 3);

    ll_module_add(&list, new_list);
    int expected_size = 3;
    int actual_size = ll_module_get_size(&list);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_size, actual_size, "Unexpected size of list");
}
void test_ShouldAddEachModuleInListToFilledList(void)
{
    struct ll_module *new_list = NULL;
    fill_modules_list(3);
    fill_given_modules_list(&new_list, 3);

    ll_module_add(&list, new_list);
    int expected_size = 6;
    int actual_size = ll_module_get_size(&list);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_size, actual_size, "Unexpected size of list");
}


TEST_CASE(0)
TEST_CASE(2)
TEST_CASE(4)
void test_ShouldInsertNewModuleInIndex(int index)
{
    fill_modules_list(5);
    struct ll_module *inserted_mod = ll_module_create("mint-insertedmod");


    ll_module_insert(&list, inserted_mod, index);
    struct ll_module *expected_mod = inserted_mod;
    struct ll_module *actual_mod = ll_module_get(&list, index);


    TEST_ASSERT_EQUAL_INT_MESSAGE(ll_module_get_size(&list), 6, "Unexpected module list size");
    TEST_ASSERT_MESSAGE(expected_mod == actual_mod, "Expected module and actual module did not match");
}
void test_ShouldGetCorrectModuleAtIndex1(void)
{
    struct ll_module *mod1 = ll_module_create("mint-mod1"), *mod2 = ll_module_create("mint-mod2"), *mod3 = ll_module_create("mint-mod3");
    ll_module_add(&list, mod1);
    ll_module_add(&list, mod2);
    ll_module_add(&list, mod3);


    struct ll_module *expected_mod = mod2;
    struct ll_module *actual_mod = ll_module_get(&list, 1);


    TEST_ASSERT_MESSAGE(expected_mod == actual_mod, "Expected module and actual module did not match");
}

TEST_CASE(-1)
TEST_CASE(4)
void test_ShouldNotGetModuleAtIndex(int index)
{
    fill_modules_list(3);


    struct ll_module *expected_mod = NULL;
    struct ll_module *actual_mod = ll_module_get(&list, index);


    TEST_ASSERT_MESSAGE(expected_mod == actual_mod, "Expected module and actual module did not match");
}
void test_ShouldGetCorrectSizeOfFilledList(void)
{
    int expected_size = 5;
    fill_modules_list(expected_size);


    int actual_size = ll_module_get_size(&list);


    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_size, actual_size, "Unexpected module list size");
}
void test_ShouldGetCorrectSizeOfEmptyList(void)
{
    fill_modules_list(5);


    int expected_size = 5;
    int actual_size = ll_module_get_size(&list);


    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_size, actual_size, "Unexpected module list size");
}
void test_ShouldSuccessfullyDelete(void)
{
    fill_modules_list(1);

    int expected_ret = 0;
    int actual_ret = ll_module_delete_at(&list, 0);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_ret, actual_ret, "Unexpected return code received");
    TEST_ASSERT_MESSAGE(NULL == list, "The modules list was not empty (NULL)");
}

TEST_CASE(-1)
TEST_CASE(2)
void test_ShouldFailToDelete(int index)
{
    fill_modules_list(1);

    int expected_ret = 1;
    int actual_ret = ll_module_delete_at(&list, index);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected_ret, actual_ret, "Unexpected return code received");
    TEST_ASSERT_MESSAGE(NULL != list, "The modules list was empty (NULL)");
}
void test_SecondModuleShouldBeFirstAfterDelete(void)
{
    struct ll_module *mod1 = ll_module_create("mint-mymod1"), *mod2 = ll_module_create("mint-mymod2");
    ll_module_add(&list, mod1);
    ll_module_add(&list, mod2);


    struct ll_module *expected_mod = mod2;
    ll_module_delete_at(&list, 0);
    struct ll_module *actual_mod = ll_module_get(&list, 0);

    TEST_ASSERT_MESSAGE(expected_mod == actual_mod, "'expected_mod' and 'actual_mod' do not match");
}
void test_FilledListShouldBeEmptyAfterDeleteAll(void)
{
    fill_modules_list(5);


    ll_module_delete_all(&list);


    TEST_ASSERT_MESSAGE(NULL == list, "The modules list was not empty (NULL)");
}
void test_EmptyListShouldBeEmptyAfterDeleteAll(void)
{
    
    ll_module_delete_all(&list);


    TEST_ASSERT_MESSAGE(NULL == list, "The modules list was not empty (NULL)");
}

// #endif // TEST