#pragma once
#include <string_view>

struct outputValues {
    static constexpr std::string_view menuOptions = R"(
            ====================================
                          Welcome to
                      Simple Cryptograph
            =====================================
    )";

    static constexpr std::string_view help = R"(
        -c [string arg] to crypt string
    )";

    static constexpr std::string_view draw = R"(
                                /M/              .,-=;//;-
                          .:/= ;MH/,    ,=/+%$XH@MM#@:
                          -$##@+$###@H@MMM#######H:.    -/H#
                    .,H@H@ X######@ -H#####@+-     -+H###@X
                      .,@##H;      +XM##M/,     =%@###@X;-
                    X%-  :M##########$.    .:%M###@%:
                    M##H,   +H@@@$/-.  ,;$M###@%,          -
                    M####M=,,---,.-%%H####M$:          ,+@##
                    @##################@/.         :%H##@$-
                    M###############H,         ;HM##M$=
                    #################.    .=$M##M$=
                    ################H..;XM##M$=          .:+
                    M###################@%=           =+@MH%
                    @#################M/.         =+H#X%=
                    =+M###############M,      ,/X#H+:,
                      .;XM###########H=   ,/X#H+:;
                        .=+HM#######M+/+HM@+=.
                            ,:/%XM####H/.
                                  ,.:=-.

                      The cake is a lie!
    )";
};