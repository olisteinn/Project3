#include <unity.h>
#include <timer.h>
#include <P_controller.h>
#include <PI_controller.h>

void test_construct(void) {
    time_set(0);
    PI_controller a(1,1);
    TEST_ASSERT_EQUAL(0, a.update(0,0)); 
}

void test_range(void) {
    time_set(0);
    PI_controller a(100,1);
    time_set(60000);
    TEST_ASSERT_EQUAL(32640, a.update(30000,0));
    time_set(0);
    a = PI_controller(100,1);
    time_set(60000);
    TEST_ASSERT_EQUAL(-32640, a.update(0,30000));
}

void test_windup(void) {
    time_set(0);
    uint32_t dt = 5000;
    PI_controller a(1.0, 0.01);
    for (int i = 1; i < 100; i++)
        time_set(dt*i);
        a.update(30000,0);
    TEST_ASSERT_EQUAL(32640, a.update(30000,0));
}

void test_precision(void) {
    double kp = 1.23;
    double ti = 3.21;
    double ki = kp/ti;
    time_set(0);
    PI_controller a(kp, ti);
    time_set(10000);
    int ref = 4321;
    int tru = 1234;
    int outp = a.update(ref, tru);
    double exp = (ref-tru)*kp + (ref-tru)*ki*0.01;

    TEST_ASSERT_TRUE(outp > exp*0.95 && outp < exp*1.05);
}

void test_poly(void) {
    time_set(0);
    P_controller p(1);
    PI_controller pi(1,1);
    controller* ctrl = &p;
    time_set(10000);
    TEST_ASSERT_EQUAL(1000, ctrl->update(1000,0)); // this does not work either
    ctrl = &pi;
    TEST_ASSERT_TRUE((int16_t)1000 < ctrl->update(1000,0));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_construct);
    RUN_TEST(test_range);
    RUN_TEST(test_windup);
    RUN_TEST(test_precision);
    RUN_TEST(test_poly);
    UNITY_END();
}