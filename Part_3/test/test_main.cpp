#include <unity.h>
#include <P_controller.h>
#include <PI_controller.h>

void test_construct(void) {
    PI_controller a(1,1);
    TEST_ASSERT_EQUAL(0, a.update(0, 0)); 
}

void test_range(void) {
    PI_controller a(100.0, 1.0);
    TEST_ASSERT_EQUAL(a.update(30000, 0),32640);
    TEST_ASSERT_EQUAL(a.update(0, 30000),-32640);
}

void test_windup(void) {
    PI_controller a(1.0, 0.01);
    for (int i = 0; i < 100; i++)
        a.update(30000, 0);
    TEST_ASSERT_EQUAL(a.update(30000, 0),32640);
}

void test_precision(void) {
    double kp = 1.23;
    double ti = 3.21;
    double ki = kp/ti;
    PI_controller a(kp, ti);
    
    int ref = 321;
    int tru = 123;
    int outp = a.update(ref, tru);
    double exp = (ref-tru)*kp + (ref-tru)*ki;

    TEST_ASSERT_TRUE(outp > exp*0.95 && outp < exp*1.05);
}

void test_poly(void) {
    P_controller p(1);
    PI_controller pi(1,1);
    controller* ctrl = &p;
    TEST_ASSERT_EQUAL(ctrl->update(1000,0),1000);
    ctrl = &pi;
    TEST_ASSERT_EQUAL(ctrl->update(1000,0),2000);
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