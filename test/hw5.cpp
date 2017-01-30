//
// Created by eugene on 1/30/17.
//
#ifdef _GTEST

#include <gtest/gtest.h>

#include "equation/parser.h"
#include "hw5.h"

struct equation_parser_f
    : ::testing::Test
{
    void test() {
        std::tie(_lhs, _rhs) = equation::parse(lhs + " = " + rhs);

        ASSERT_EQ(_lhs->to_string(), lhs);
        ASSERT_EQ(_rhs->to_string(), rhs);
    }

    std::string lhs;
    std::string rhs;

private:
    equation::vertex_ptr_t _lhs;
    equation::vertex_ptr_t _rhs;
};

TEST_F(equation_parser_f, just_variables) {
    lhs = "x";
    rhs = "y";
    test();
}

TEST_F(equation_parser_f, single_argument_functions) {
    lhs = "f(z)";
    rhs = "h(y)";
    test();
}

TEST_F(equation_parser_f, complex_functions) {
    lhs = "f(g(x, y, a(x, y, z)), z)";
    rhs = "h(y, b(j, k, i, i))";
    test();
}

TEST(hw5, trivial_just_vars) {
    std::string const eq = "x = y";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "x = y\n");
}

TEST(hw5, trivial_with_function) {
    std::string const eq = "f(y, g(z))  =  x  ";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "x = f(y, g(z))\n");
}

TEST(hw5, simple_equation) {
    std::string const eq = "f(y, g(z))  =  f(x, y)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "y = g(z)\n"
                   "x = g(z)\n");
}

TEST(hw5, solvable1) {
    std::string const eq = "f(x, g(y)) = f(e(g(f(t, z))), t)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "t = g(y)\n"
                   "x = e(g(f(g(y), z)))\n");
}

TEST(hw5, solvable2) {
    std::string const eq = "f1(k,f2(l,f3(m,f4(n,f5(o)))))=f1(f2(f3(f4(f5(o),n),m),l),k)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "k = f2(f3(f4(f5(o), f5(o)), f4(f5(o), f5(o))), f3(f4(f5(o), f5(o)), f4(f5(o), f5(o))))\n"
                   "l = f3(f4(f5(o), f5(o)), f4(f5(o), f5(o)))\n"
                   "m = f4(f5(o), f5(o))\n"
                   "n = f5(o)\n");
}

TEST(hw5, dificult_equation) {
    std::string const eq = "f(f(x,g(y)),f(e(g(f(t,z))),t))=f(m,m)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "m = f(e(g(f(g(y), z))), g(y))\n"
                   "t = g(y)\n"
                   "x = e(g(f(g(y), z)))\n");
}

TEST(hw5, simple_system_equation) {
    std::string const eq = "f(g(z, y), h(x, x)) = u\n"
                           "u = f(v, w)\n"
                           "v = g(t, f(m, m))\n"
                           "w = h(y, y)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "u = f(g(z, f(m, m)), h(f(m, m), f(m, m)))\n"
                   "w = h(f(m, m), f(m, m))\n"
                   "v = g(z, f(m, m))\n"
                   "x = f(m, m)\n"
                   "y = f(m, m)\n"
                   "t = z\n");
}

TEST(hw5, solvable3) {
    std::string const eq = "e20(h79(f80(h99(a77(z25,m70,k82,q28,u48),g83(w4),b23(s74,y50,j58),h72(m89,k67,y98),a24(m37)),c29(h20(t62,w19,j28,r11),b99(w36,k41,q66),d76(o89,k50),h48(i31,s24,s94,s26),b13(l83,o3,k18,u23)),e97(f92(i17,k98,v60,k89,l54)),h50(a30(r45,p38,y50,i36),a42(o96,q4,p26,v7,s15),w71,b91(x87),d92(k0,u11,w68)),y93),g14(g66(v5))),d35(a25(b85(e43(o98,l75,j79,z73),g20(z5,w27,p80,m66)),b71(d38(m7,t5,i12,o65),f39(s36,w76,w48),e10(n36,u42,q50,r90,y68),d53(q93,r65,r37),t15),d53(c36(s42,u9),f31(u84,p34,m94,l88,y54),f64(i51,j10,i27)),g47(e70(o96,l61,o1,v23))),a93(d38(g76(t14,s21,n5,w73,o74),c72(k90,n14,j91,j44,j17)),h58(d81(q49,t90,t13,m76,r47),f40(q94,y0,t83)),h10(c66(w26),g27(k96,w93),c16(j77,q54,w97,t54,o21),g31(z22,t97),f71(l30,m59,z77,x44))),e9(h38(a80(m11,z59,v15),f19(l21,j13,x42)),e79(g72(t7,m44,z83),b73(u54,m4,r18,q98,p39),g89(q35,y84)),h60(x9)),a92(f71(g8(n58,y37,z24,x53),b67(t51,v96,l91,s97),f73(p39,z76,l15,z33,y49)),f32(c94(y51)))),z16,d72(h88(a81(h97(z95,m96,p42,w27),a80(l77,l51,x26),a74(q44,k61,p1)),g38(c49(i96,m36,t45))),c48(b24(e91(y57,k7,w3),q98,c56(z61,y89,u67)),e36(a50(o28,p88,i48,u72,w71),e55(o60)),g75(g38(u85),e86(i41,n43,s6,r84),d25(m33),s76),b97(f99(u35,t76,l43,y73)),g98(f75(v0,k3),b11(u58,m34)))),e88(g38(l74,c14(q82,f1(x61,q13),e18(y55,x16,r29)),e60(f82(x10,v0,k98,v40,p91),h97(j54,o45,v76,r81),a74(z28,k60,j48,q88),b42(t56,o16,n98),e83(y10)),e25(c13(k11,u87,x15,y44),g65(j69,l66,i89,w42,o17),b43(t77,w29,n97,u25,r61),g52(v35)),e9(c2(z61,t39,u93,y43),g65(z58,i96),a76(v77,r28,p95,n86,m95),h43(n88,m94,j5,s57))),f33(h88(c45(l2,s18,j88)),c31(n94,h60(j52,u9),h28(n65,j77,r54,t59),h85(m44),e66(t73,o68,n17))),j25,e18(d10(h99(p86,i52,v95),c44(p71,t97,k24),e80(n97,n93,z46))),f82(c38(g62(j10,n72,v84,y80),f43(z96,o84,q8,s1,o77),a10(n81,z95)),g41(f5(w95,u47,k90),g12(u45),a81(j5)),e68(f67(p15,j60,q50,x95,i63),a13(u9)),e36(m68,b71(z54,z73)))))=e20(h79(f80(h99(a77(z25,m70,k82,q28,x57),g83(w4),b23(s74,y50,p12),u4,a24(m37)),c29(h20(k77,w19,w29,n1),b99(w36,k41,q66),d76(o89,k50),h48(i31,s24,p6,s26),b13(l83,o3,k18,u23)),e97(f92(v41,k98,x5,k89,l54)),h50(a30(r14,p38,y50,i36),a42(o96,q4,p26,v7,s15),g29(v88,z0,t93,r37),b91(x87),d92(k0,u11,j87)),d85(t91)),g14(g66(b31(y64,n76,r11,n5,r10)))),z32,e87(b72(c70(h99(n43),h73(k53,r71,v90),a12(i30,p89,p4),g78(k20),h36(q91,y66,q76,m49)),g20(b24(r90,k3,s56,x43),a19(k56,q44))),e25(g61(f40(t27,l9,o49,w16,y87),g91(r52,u65,t36,z15)))),d72(h88(a81(h97(z95,m96,p42,w27),a80(l77,l51,x26),a74(q44,s95,p1)),g38(c49(i96,m36,t45))),c48(b24(e91(y57,k7,w3),e91(w42),c56(z61,j36,i38)),e36(a50(o28,p88,i48,u72,w71),e55(o60)),g75(g38(u85),e86(i41,n43,s6,m91),d25(m33),g94(k99,l98)),b97(f99(u35,t76,l43,y73)),g98(f75(v0,k3),m57))),e88(g38(e71(e39(w53,i31,q73),f42(s33,z81)),c14(c16(v16,v57),f1(l83,q13),e18(y55,x16,r29)),e60(f82(x10,v0,k98,v40,p91),v59,a74(u75,k60,j48,q88),b42(t56,o16,n98),e83(y10)),m12,e9(c2(z61,t39,u93,y43),g65(z58,i96),a76(v77,r28,m23,n86,m95),h43(n88,m94,j5,s57))),f33(h88(c45(j46,s18,j88)),c31(b50(o21),h60(j52,u9),h28(y36,s21,r54,t59),h85(k52),e66(t73,o68,t88))),b69(z30,d93(c70(s78,y41,q53),d16(l56),h81(u61,o65,s15),g44(s53,v88,r93,j27)),c62(b91(w50,q92),d41(j52,z16,o67))),e18(d10(h99(p86,i52,v95),c44(p71,j4,k24),e80(n97,n93,j58))),f82(c38(g62(j10,n72,z6,y80),f43(k23,o84,q8,s1,o77),a10(n81,z95)),g41(f5(w95,u47,k90),g12(o66),a81(j5)),i60,e36(f72(k46),b71(z54,z73)))))";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "m68 = f72(k46)\nv5 = b31(y64, n76, r11, n5, r10)\nz32 = d35(a25(b85(e43(o98, l75, j79, z73), g20(z5, w27, p80, m66)), b71(d38(m7, t5, i12, o65), f39(s36, w76, w48), e10(n36, u42, q50, r90, y68), d53(q93, r65, r37), t15), d53(c36(s42, u9), f31(u84, p34, m94, l88, y54), f64(i51, j10, i27)), g47(e70(o96, l61, o1, v23))), a93(d38(g76(t14, s21, n5, w73, o74), c72(k90, n14, j91, j44, j17)), h58(d81(q49, t90, t13, m76, r47), f40(q94, y0, t83)), h10(c66(w26), g27(k96, w93), c16(s21, q54, w97, t54, o21), g31(z22, t97), f71(l30, m59, z77, x44))), e9(h38(a80(m11, z59, v15), f19(l21, j13, x42)), e79(g72(t7, m44, z83), b73(u54, m4, r18, e91(w42), p39), g89(q35, y84)), h60(x9)), a92(f71(g8(n58, y37, z24, x53), b67(t51, v96, l91, s97), f73(p39, z76, l15, z33, y49)), f32(c94(y51))))\nz16 = e87(b72(c70(h99(n43), h73(k53, r71, v90), a12(i30, p89, p4), g78(k20), h36(q91, y66, q76, m49)), g20(b24(r90, k3, s56, x43), a19(k56, q44))), e25(g61(f40(t27, l9, o49, w16, y87), g91(r52, u65, t36, z15))))\nm57 = b11(u58, m34)\nm23 = p95\nn17 = t88\nj25 = b69(z30, d93(c70(s78, y41, q53), d16(l56), h81(u61, o65, s15), g44(s53, v88, r93, j27)), c62(b91(w50, q92), d41(j52, e87(b72(c70(h99(n43), h73(k53, r71, v90), a12(i30, p89, p4), g78(k20), h36(q91, y66, q76, m49)), g20(b24(r90, k3, s56, x43), a19(k56, q44))), e25(g61(f40(t27, l9, o49, w16, y87), g91(r52, u65, t36, z15)))), o67)))\nj58 = z46\nk23 = z96\no66 = u45\ni60 = e68(f67(p15, j60, q50, x95, i63), a13(u9))\ny93 = d85(t91)\nk61 = s95\ni38 = u67\nj36 = y89\ns76 = g94(k99, l98)\nm91 = r84\nq98 = e91(w42)\nl74 = e71(e39(w53, i31, q73), f42(s33, z81))\nl83 = x61\nu75 = z28\nm12 = e25(c13(k11, u87, x15, y44), g65(j69, l66, i89, w42, o17), b43(t77, w29, n97, u25, r61), g52(v35))\nv59 = h97(j54, o45, v76, r81)\nq82 = c16(v16, v57)\nj87 = w68\nw71 = g29(v88, z0, t93, r37)\nj46 = l2\nn94 = b50(o21)\nr14 = r45\nj77 = s21\nk52 = m44\nn65 = y36\nv60 = x5\ni17 = v41\nj4 = t97\np6 = s94\nn1 = r11\nv84 = z6\nj28 = w29\nu4 = h72(m89, k67, y98)\nk77 = t62\np12 = z46\nu48 = x57\n");

}

TEST(hw5DeathTest, not_solving) {
    std::string const eq = "f(x)=y\n"
                           "f(x)=f(y)";

    ASSERT_DEATH(hw5::main(eq), "");
}

#endif // _GTEST

