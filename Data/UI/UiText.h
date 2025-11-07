#pragma once
#include <string_view>

struct Support {
    static constexpr std::string_view help = R"(
    ========================================================
    |                     Welcome to                       |
    |                 Simple Cryptograph                   |
    ========================================================
    |   This help text:                                    |
    |   -h                                                 |
    ========================================================
    |   Create password for encryption:                    |
    |   -v -p [password]                                   |
    ========================================================
    |   File encryption:                                   |
    |   -c -f [filename.ext] -p [password]                 |
    ========================================================
    |   File decryption:                                   |
    |   -d -f [filename.ext] -p [password]                 |
    ========================================================
    |   Masterpiece:                                       |
    |   -q                                                 |
    ========================================================
    |   OpenSSl Error:                                     |
    |   error:[error code]:[library name]::[reason string] |
    ========================================================
    )";
};

struct Art {
    static constexpr std::string_view drawCake = R"(
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

struct EncryptionOutput {
    static constexpr std::string_view encryptCurrent = "\nEncrypting file...\n";
    static constexpr std::string_view encryptSuccess = "\nFile encrypted successfully.\n";
    static constexpr std::string_view decryptCurrent = "\nDecrypting file...\n";
    static constexpr std::string_view decryptSuccess = "\nFile decrypted successfully...\n";
};