#include "s21_SmartCalc.h"

#include <check.h>

START_TEST(test_1) {
  char a[255] = "2*4*5*(6)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 240, 0.000001);
}
END_TEST

START_TEST(test_2) {
  char a[255] = "8*sin(6)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, -2.23532398559, 0.000001);
}
END_TEST

START_TEST(test_3) {
  char a[255] = "log(16)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 1.20411998266, 0.001);
}
END_TEST

START_TEST(test_4) {
  char a[255] = "6^5-14*2";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 7748, 0.000001);
}
END_TEST

START_TEST(test_5) {
  char a[255] = "6mod4";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 2, 0.000001);
}
END_TEST

START_TEST(test_6) {
  char a[255] = "-0";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0, 0.00001);
}
END_TEST

START_TEST(test_7) {
  char a[255] = "qwerty";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0, 0.00001);
}
END_TEST

START_TEST(test_8) {
  char a[255] = "-25+6-8";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, -27, 0.00001);
}
END_TEST

START_TEST(test_9) {
  char a[255] = "+10+10+5";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 25, 0.000001);
}
END_TEST

START_TEST(test_10) {
  char a[255] = "15+75*1/3-42+3^3";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 25, 0.000001);
}
END_TEST

START_TEST(test_11) {
  char a[255] = "asin(12*x)";
  double res = s21_parser(a, 0.05);
  ck_assert_double_eq_tol(res, 0.643501109, 0.000001);
}
END_TEST

START_TEST(test_12) {
  char a[255] = "acos(3*0.08)";
  double res = s21_parser(a, 0.08);
  ck_assert_double_eq_tol(res, 1.32843048, 0.001);
}
END_TEST

START_TEST(test_13) {
  char a[255] = "atan(-8*x)";
  double res = s21_parser(a, 0.014);
  ck_assert_double_eq_tol(res, -0.111535184, 0.000001);
}
END_TEST

START_TEST(test_14) {
  char a[255] = "tan(-6*x)";
  double res = s21_parser(a, 2);
  ck_assert_double_eq_tol(res, 0.63585992866, 0.000001);
}
END_TEST

START_TEST(test_15) {
  char a[255] = "sqrt(4*x)";
  double res = s21_parser(a, 45);
  ck_assert_double_eq_tol(res, 13.416407865, 0.00001);
}
END_TEST

START_TEST(test_16) {
  char a[255] = "ln(10*x)";
  double res = s21_parser(a, 2);
  ck_assert_double_eq_tol(res, 2.99573, 0.00001);
}
END_TEST

START_TEST(test_17) {
  char a[255] = "log(10*x)";
  double res = s21_parser(a, 2);
  ck_assert_double_eq_tol(res, 1.30103, 0.00001);
}
END_TEST

START_TEST(test_18) {
  char a[255] = "()";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0, 0.000001);
}
END_TEST

START_TEST(test_19) {
  char a[255] = "3-(-3)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 6, 0.000001);
}
END_TEST

START_TEST(test_20) {
  char a[255] = "3-(+3)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0, 0.000001);
}
END_TEST

START_TEST(test_21) {
  char a[255] = "1+2+3+4*5*6^7";
  double res = s21_parser(a, 0);
  ck_assert_int_eq((int)res, 5598726);
}
END_TEST

START_TEST(test_22) {
  char a[255] = "123.456+2*3^4";
  double res = s21_parser(a, 0);
  ck_assert_double_eq(res, 285.456);
}
END_TEST

START_TEST(test_23) {
  char a[255] = "(8+2*5)/(1+3*2-4)";
  double res = s21_parser(a, 0);
  ck_assert_double_eq(res, 6);
}
END_TEST

START_TEST(test_24) {
  char a[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double res = s21_parser(a, 0);
  ck_assert_double_eq(res, 10);
}
END_TEST

START_TEST(test_25) {
  char a[255] = "cos(1*2)-1";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, -1.41614683655, 0.000001);
}
END_TEST

START_TEST(test_26) {
  char a[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, -1.83907152908, 0.000001);
}
END_TEST

START_TEST(test_27) {
  char a[255] = "sin(cos(5))";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0.27987335076, 0.000001);
}
END_TEST

START_TEST(test_28) {
  char a[255] = "2.33mod1";
  double res = s21_parser(a, 0);
  ck_assert_double_eq_tol(res, 0.33, 0.000001);
}
END_TEST

START_TEST(test_29) {
  char a[255] = "3+4*2/(1-5)^2";
  double res = s21_parser(a, 0);
  ck_assert_double_eq(res, 3.5);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_smart_calc: ");
  TCase *tc1_1 = tcase_create("s21_smart_calc: ");
  SRunner *sr = srunner_create(s1);
  int res;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);
  tcase_add_test(tc1_1, test_29);

  srunner_run_all(sr, CK_ENV);
  res = srunner_ntests_failed(sr);
  srunner_free(sr);
  return res == 0 ? 0 : 1;
}
