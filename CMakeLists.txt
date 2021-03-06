cmake_minimum_required(VERSION 3.9)
project(SOFTCoin)

OPTION(QT5_BUILD "Use Qt5" ON)

##############################################################################################################
########## Check CPU Component                                                                      ##########
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_CXX_FLAGS_DEBUG   "-Wall -ggdb3 -O0 -fno-inline -rdynamic")
    SET(CMAKE_C_FLAGS_DEBUG     "-Wall -ggdb3 -O0 -fno-inline -rdynamic")
    #   SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++11 -ggdb3 -O2")
    #   SET(CMAKE_C_FLAGS_RELEASE   "-Wall            -ggdb3 -O2")
    #   SET(CMAKE_CXX_FLAGS         "-Wall -std=c++11 -ggdb3")
    #   SET(CMAKE_C_FLAGS           "-Wall            -ggdb3")
ENDIF (CMAKE_COMPILER_IS_GNUCC)

## matches Linux Clang and also AppleClang
IF (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS_DEBUG   "-Wall -ggdb3 -O0 -fno-inline")
    SET(CMAKE_C_FLAGS_DEBUG     "-Wall -ggdb3 -O0 -fno-inline")
    #   SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++11 -ggdb3 -O2")
    #   SET(CMAKE_C_FLAGS_RELEASE   "-Wall            -ggdb3 -O2")
    #   SET(CMAKE_CXX_FLAGS         "-Wall -std=c++11 -ggdb3")
    #   SET(CMAKE_C_FLAGS           "-Wall            -ggdb3")
ENDIF()

#Convert our simpler command line option to the CMake style
#None, Debug, Release, .. or custom ones
IF (CMAKE_BUILD_TYPE MATCHES [Dd]ebug)
    message(STATUS "Debug build")
    SET(CMAKE_BUILD_TYPE Debug)
    add_definitions(-DDEBUG -DQT_DEBUG)
    SET(FUSION_DEBUG TRUE)
ELSE()
    message(STATUS "non-debug build")
    SET(FUSION_DEBUG FALSE)
    add_definitions(-DNDEBUG -DQT_NO_DEBUG)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
ENDIF()

# Lets disable Wall warnings due the MSVC too much talkative
# output. Wall can slow down compiletion up to hours and
# my boxes can boil eggs too.
# MSVC, MSVC_IDE, MSVC60, MSVC70, MSVC71, MSVC80, CMAKE_COMPILER_2005
IF (MSVC)
    SET(CXX_WARNINGS "")
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ELSE (MSVC)
    SET(CXX_WARNINGS "-Wall")
ENDIF (MSVC)

##############################################################################################################
########## Find Dependencies                                                                        ##########

SET(QT_MT_REQUIRED true)
SET(QT_USE_QTNETWORK TRUE)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QTWEBKIT TRUE)
#SET(CMAKE_AUTOMOC ON)
IF(QT5_BUILD)

    SET(QT_FOUND true)
    SET(CMAKE_PREFIX_PATH "$ENV{QTDIR}\\") # multiple paths do not work
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Network REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    find_package(Qt5Sql REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Xml REQUIRED)
    find_package(Qt5LinguistTools)
    IF(APPLE)
        find_package(Qt5MacExtras REQUIRED)
    ENDIF()
    SET(QT_INCLUDES
            ${Qt5Core_INCLUDE_DIRS}
            ${Qt5Gui_INCLUDE_DIRS}
            ${Qt5Network_INCLUDE_DIRS}
            ${Qt5PrintSupport_INCLUDE_DIRS}
            ${Qt5Sql_INCLUDE_DIRS}
            ${Qt5Widgets_INCLUDE_DIRS}
            ${Qt5Xml_INCLUDE_DIRS}
            )
    IF(APPLE)
        LIST(APPEND QT_INCLUDES ${Qt5MacExtras_INCLUDE_DIRS})
    ENDIF()
    include_directories(${QT_INCLUDES})
    # SET(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
    # SET(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}   ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
    # STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
    # SET(${_flags_var_name}      "${${_flags_var_name}} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
    # SET("CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
    # # prevent error "You must build your code with position independent code if Qt was built with..
    if (Qt5_POSITION_INDEPENDENT_CODE)
        SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
    endif()
ELSE()
    SET(QT_MIN_VERSION "4.8.0")
    SET(QT_USE_QTSQL TRUE)
    SET(QT_USE_QTNETWORK TRUE)
    SET(QT_USE_QTXML TRUE)
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE( ${QT_USE_FILE} )
ENDIF()
IF (QT_FOUND)
    MESSAGE("Qt Found OK")
    #Add our Qt definitions
    ADD_DEFINITIONS(
            ${QT_DEFINITIONS}
            -DQT_CORE_LIB
            -DQT_GUI_LIB
            -DQT_THREAD_LIB
    )
ELSE(QT_FOUND)
    MESSAGE(FATAL_ERROR "No Qt found")
ENDIF(QT_FOUND)

##############################################################################################################
########## Add Executables                                                                          ##########

add_executable(fusion_core
        src/bench/base58.cpp
        src/bench/bench.cpp
        src/bench/bench.h
        src/bench/bench_softcoin.cpp
        src/bench/crypto_hash.cpp
        src/bench/Examples.cpp
        src/bench/rollingbloom.cpp
        src/compat/byteswap.h
        src/compat/endian.h
        src/compat/glibc_compat.cpp
        src/compat/glibc_sanity.cpp
        src/compat/glibcxx_sanity.cpp
        src/compat/sanity.h
        src/compat/strnlen.cpp
        src/consensus/cfund.cpp
        src/consensus/cfund.h
        src/consensus/consensus.h
        src/consensus/merkle.cpp
        src/consensus/merkle.h
        src/consensus/params.h
        src/consensus/validation.h
        src/crypto/ctaes/bench.c
        src/crypto/ctaes/ctaes.c
        src/crypto/ctaes/ctaes.h
        src/crypto/ctaes/test.c
        src/crypto/aes.cpp
        src/crypto/aes.h
        src/crypto/common.h
        src/crypto/hmac_sha256.cpp
        src/crypto/hmac_sha256.h
        src/crypto/hmac_sha512.cpp
        src/crypto/hmac_sha512.h
        src/crypto/ripemd160.cpp
        src/crypto/ripemd160.h
        src/crypto/sha1.cpp
        src/crypto/sha1.h
        src/crypto/sha256.cpp
        src/crypto/sha256.h
        src/crypto/sha512.cpp
        src/crypto/sha512.h
        src/leveldb/db/autocompact_test.cc
        src/leveldb/db/builder.cc
        src/leveldb/db/builder.h
        src/leveldb/db/c.cc
        src/leveldb/db/c_test.c
        src/leveldb/db/corruption_test.cc
        src/leveldb/db/db_bench.cc
        src/leveldb/db/db_impl.cc
        src/leveldb/db/db_impl.h
        src/leveldb/db/db_iter.cc
        src/leveldb/db/db_iter.h
        src/leveldb/db/db_test.cc
        src/leveldb/db/dbformat.cc
        src/leveldb/db/dbformat.h
        src/leveldb/db/dbformat_test.cc
        src/leveldb/db/dumpfile.cc
        src/leveldb/db/filename.cc
        src/leveldb/db/filename.h
        src/leveldb/db/filename_test.cc
        src/leveldb/db/leveldb_main.cc
        src/leveldb/db/log_format.h
        src/leveldb/db/log_reader.cc
        src/leveldb/db/log_reader.h
        src/leveldb/db/log_test.cc
        src/leveldb/db/log_writer.cc
        src/leveldb/db/log_writer.h
        src/leveldb/db/memtable.cc
        src/leveldb/db/memtable.h
        src/leveldb/db/repair.cc
        src/leveldb/db/skiplist.h
        src/leveldb/db/skiplist_test.cc
        src/leveldb/db/snapshot.h
        src/leveldb/db/table_cache.cc
        src/leveldb/db/table_cache.h
        src/leveldb/db/version_edit.cc
        src/leveldb/db/version_edit.h
        src/leveldb/db/version_edit_test.cc
        src/leveldb/db/version_set.cc
        src/leveldb/db/version_set.h
        src/leveldb/db/version_set_test.cc
        src/leveldb/db/write_batch.cc
        src/leveldb/db/write_batch_internal.h
        src/leveldb/db/write_batch_test.cc
        src/leveldb/doc/bench/db_bench_sqlite3.cc
        src/leveldb/doc/bench/db_bench_tree_db.cc
        src/leveldb/helpers/memenv/memenv.cc
        src/leveldb/helpers/memenv/memenv.h
        src/leveldb/helpers/memenv/memenv_test.cc
        src/leveldb/include/leveldb/c.h
        src/leveldb/include/leveldb/cache.h
        src/leveldb/include/leveldb/comparator.h
        src/leveldb/include/leveldb/db.h
        src/leveldb/include/leveldb/dumpfile.h
        src/leveldb/include/leveldb/env.h
        src/leveldb/include/leveldb/filter_policy.h
        src/leveldb/include/leveldb/iterator.h
        src/leveldb/include/leveldb/options.h
        src/leveldb/include/leveldb/slice.h
        src/leveldb/include/leveldb/status.h
        src/leveldb/include/leveldb/table.h
        src/leveldb/include/leveldb/table_builder.h
        src/leveldb/include/leveldb/write_batch.h
        src/leveldb/issues/issue178_test.cc
        src/leveldb/issues/issue200_test.cc
        src/leveldb/port/win/stdint.h
        src/leveldb/port/atomic_pointer.h
        src/leveldb/port/port.h
        src/leveldb/port/port_example.h
        src/leveldb/port/port_posix.cc
        src/leveldb/port/port_posix.h
        src/leveldb/port/port_win.cc
        src/leveldb/port/port_win.h
        src/leveldb/port/thread_annotations.h
        src/leveldb/table/block.cc
        src/leveldb/table/block.h
        src/leveldb/table/block_builder.cc
        src/leveldb/table/block_builder.h
        src/leveldb/table/filter_block.cc
        src/leveldb/table/filter_block.h
        src/leveldb/table/filter_block_test.cc
        src/leveldb/table/format.cc
        src/leveldb/table/format.h
        src/leveldb/table/iterator.cc
        src/leveldb/table/iterator_wrapper.h
        src/leveldb/table/merger.cc
        src/leveldb/table/merger.h
        src/leveldb/table/table.cc
        src/leveldb/table/table_builder.cc
        src/leveldb/table/table_test.cc
        src/leveldb/table/two_level_iterator.cc
        src/leveldb/table/two_level_iterator.h
        src/leveldb/util/arena.cc
        src/leveldb/util/arena.h
        src/leveldb/util/arena_test.cc
        src/leveldb/util/bloom.cc
        src/leveldb/util/bloom_test.cc
        src/leveldb/util/cache.cc
        src/leveldb/util/cache_test.cc
        src/leveldb/util/coding.cc
        src/leveldb/util/coding.h
        src/leveldb/util/coding_test.cc
        src/leveldb/util/comparator.cc
        src/leveldb/util/crc32c.cc
        src/leveldb/util/crc32c.h
        src/leveldb/util/crc32c_test.cc
        src/leveldb/util/env.cc
        src/leveldb/util/env_posix.cc
        src/leveldb/util/env_test.cc
        src/leveldb/util/env_win.cc
        src/leveldb/util/filter_policy.cc
        src/leveldb/util/hash.cc
        src/leveldb/util/hash.h
        src/leveldb/util/hash_test.cc
        src/leveldb/util/histogram.cc
        src/leveldb/util/histogram.h
        src/leveldb/util/logging.cc
        src/leveldb/util/logging.h
        src/leveldb/util/mutexlock.h
        src/leveldb/util/options.cc
        src/leveldb/util/posix_logger.h
        src/leveldb/util/random.h
        src/leveldb/util/status.cc
        src/leveldb/util/testharness.cc
        src/leveldb/util/testharness.h
        src/leveldb/util/testutil.cc
        src/leveldb/util/testutil.h
        src/policy/fees.cpp
        src/policy/fees.h
        src/policy/policy.cpp
        src/policy/policy.h
        src/policy/rbf.cpp
        src/policy/rbf.h
        src/primitives/block.cpp
        src/primitives/block.h
        src/primitives/transaction.cpp
        src/primitives/transaction.h
        src/qt/test/paymentrequestdata.h
        src/qt/test/paymentservertests.cpp
        src/qt/test/paymentservertests.h
        src/qt/test/test_main.cpp
        src/qt/test/uritests.cpp
        src/qt/test/uritests.h
        src/qt/addressbookpage.cpp
        src/qt/addressbookpage.h
        src/qt/addresstablemodel.cpp
        src/qt/addresstablemodel.h
        src/qt/askpassphrasedialog.cpp
        src/qt/askpassphrasedialog.h
        src/qt/bantablemodel.cpp
        src/qt/bantablemodel.h
        src/qt/clientmodel.cpp
        src/qt/clientmodel.h
        src/qt/coincontroldialog.cpp
        src/qt/coincontroldialog.h
        src/qt/coincontroltreewidget.cpp
        src/qt/coincontroltreewidget.h
        src/qt/csvmodelwriter.cpp
        src/qt/csvmodelwriter.h
        src/qt/editaddressdialog.cpp
        src/qt/editaddressdialog.h
        src/qt/getaddresstoreceive.cpp
        src/qt/getaddresstoreceive.h
        src/qt/guiconstants.h
        src/qt/guiutil.cpp
        src/qt/guiutil.h
        src/qt/intro.cpp
        src/qt/intro.h
        src/qt/listview.h
        src/qt/macdockiconhandler.h
        src/qt/macnotificationhandler.h
        src/qt/softcoin.cpp
        src/qt/softcoinaddressvalidator.cpp
        src/qt/softcoinaddressvalidator.h
        src/qt/softcoinamountfield.cpp
        src/qt/softcoinamountfield.h
        src/qt/softcoingui.cpp
        src/qt/softcoingui.h
        src/qt/softcoinstrings.cpp
        src/qt/softcoinunits.cpp
        src/qt/softcoinunits.h
        src/qt/softnodeinit.cpp
        src/qt/softnodeinit.h
        src/qt/softnodeitem.cpp
        src/qt/softnodeitem.h
        src/qt/softnodesetup.cpp
        src/qt/softnodesetup.h
        src/qt/networkstyle.cpp
        src/qt/networkstyle.h
        src/qt/notificator.cpp
        src/qt/notificator.h
        src/qt/openuridialog.cpp
        src/qt/openuridialog.h
        src/qt/optionsdialog.cpp
        src/qt/optionsdialog.h
        src/qt/optionsmodel.cpp
        src/qt/optionsmodel.h
        src/qt/overviewpage.cpp
        src/qt/overviewpage.h
        src/qt/paymentrequestplus.cpp
        src/qt/paymentrequestplus.h
        src/qt/paymentserver.cpp
        src/qt/paymentserver.h
        src/qt/peertablemodel.cpp
        src/qt/peertablemodel.h
        src/qt/platformstyle.cpp
        src/qt/platformstyle.h
        src/qt/qvalidatedlineedit.cpp
        src/qt/qvalidatedlineedit.h
        src/qt/qvaluecombobox.cpp
        src/qt/qvaluecombobox.h
        src/qt/receivecoinsdialog.cpp
        src/qt/receivecoinsdialog.h
        src/qt/receiverequestdialog.cpp
        src/qt/receiverequestdialog.h
        src/qt/recentrequeststablemodel.cpp
        src/qt/recentrequeststablemodel.h
        src/qt/rpcconsole.cpp
        src/qt/rpcconsole.h
        src/qt/sendcoinsdialog.cpp
        src/qt/sendcoinsdialog.h
        src/qt/sendcoinsentry.cpp
        src/qt/sendcoinsentry.h
        src/qt/signverifymessagedialog.cpp
        src/qt/signverifymessagedialog.h
        src/qt/skinize.cpp
        src/qt/skinize.h
        src/qt/splashscreen.cpp
        src/qt/splashscreen.h
        src/qt/trafficgraphwidget.cpp
        src/qt/trafficgraphwidget.h
        src/qt/transactiondesc.cpp
        src/qt/transactiondesc.h
        src/qt/transactiondescdialog.cpp
        src/qt/transactiondescdialog.h
        src/qt/transactionfilterproxy.cpp
        src/qt/transactionfilterproxy.h
        src/qt/transactionrecord.cpp
        src/qt/transactionrecord.h
        src/qt/transactiontablemodel.cpp
        src/qt/transactiontablemodel.h
        src/qt/transactionview.cpp
        src/qt/transactionview.h
        src/qt/ui_getaddresstoreceive.h
        src/qt/ui_softnodeinit.h
        src/qt/ui_softnodeitem.h
        src/qt/ui_softnodesetup.h
        src/qt/utilitydialog.cpp
        src/qt/utilitydialog.h
        src/qt/walletframe.cpp
        src/qt/walletframe.h
        src/qt/walletmodel.cpp
        src/qt/walletmodel.h
        src/qt/walletmodeltransaction.cpp
        src/qt/walletmodeltransaction.h
        src/qt/walletview.cpp
        src/qt/walletview.h
        src/qt/winshutdownmonitor.cpp
        src/qt/winshutdownmonitor.h
        src/rpc/blockchain.cpp
        src/rpc/client.cpp
        src/rpc/client.h
        src/rpc/mining.cpp
        src/rpc/misc.cpp
        src/rpc/net.cpp
        src/rpc/protocol.cpp
        src/rpc/protocol.h
        src/rpc/rawtransaction.cpp
        src/rpc/register.h
        src/rpc/server.cpp
        src/rpc/server.h
        src/script/interpreter.cpp
        src/script/interpreter.h
        src/script/ismine.cpp
        src/script/ismine.h
        src/script/softcoinconsensus.cpp
        src/script/softcoinconsensus.h
        src/script/script.cpp
        src/script/script.h
        src/script/script_error.cpp
        src/script/script_error.h
        src/script/sigcache.cpp
        src/script/sigcache.h
        src/script/sign.cpp
        src/script/sign.h
        src/script/standard.cpp
        src/script/standard.h
        src/secp256k1/contrib/lax_der_parsing.c
        src/secp256k1/contrib/lax_der_parsing.h
        src/secp256k1/contrib/lax_der_privatekey_parsing.c
        src/secp256k1/contrib/lax_der_privatekey_parsing.h
        src/secp256k1/include/secp256k1.h
        src/secp256k1/include/secp256k1_ecdh.h
        src/secp256k1/include/secp256k1_recovery.h
        src/secp256k1/include/secp256k1_schnorr.h
        src/secp256k1/src/java/org_softcoin_NativeSecp256k1.c
        src/secp256k1/src/java/org_softcoin_NativeSecp256k1.h
        src/secp256k1/src/modules/ecdh/main_impl.h
        src/secp256k1/src/modules/ecdh/tests_impl.h
        src/secp256k1/src/modules/recovery/main_impl.h
        src/secp256k1/src/modules/recovery/tests_impl.h
        src/secp256k1/src/modules/schnorr/main_impl.h
        src/secp256k1/src/modules/schnorr/schnorr.h
        src/secp256k1/src/modules/schnorr/schnorr_impl.h
        src/secp256k1/src/modules/schnorr/tests_impl.h
        src/secp256k1/src/basic-config.h
        src/secp256k1/src/bench.h
        src/secp256k1/src/bench_ecdh.c
        src/secp256k1/src/bench_internal.c
        src/secp256k1/src/bench_recover.c
        src/secp256k1/src/bench_schnorr_verify.c
        src/secp256k1/src/bench_sign.c
        src/secp256k1/src/bench_verify.c
        src/secp256k1/src/ecdsa.h
        src/secp256k1/src/ecdsa_impl.h
        src/secp256k1/src/eckey.h
        src/secp256k1/src/eckey_impl.h
        src/secp256k1/src/ecmult.h
        src/secp256k1/src/ecmult_const.h
        src/secp256k1/src/ecmult_const_impl.h
        src/secp256k1/src/ecmult_gen.h
        src/secp256k1/src/ecmult_gen_impl.h
        src/secp256k1/src/ecmult_impl.h
        src/secp256k1/src/field.h
        src/secp256k1/src/field_10x26.h
        src/secp256k1/src/field_10x26_impl.h
        src/secp256k1/src/field_5x52.h
        src/secp256k1/src/field_5x52_asm_impl.h
        src/secp256k1/src/field_5x52_impl.h
        src/secp256k1/src/field_5x52_int128_impl.h
        src/secp256k1/src/field_impl.h
        src/secp256k1/src/gen_context.c
        src/secp256k1/src/group.h
        src/secp256k1/src/group_impl.h
        src/secp256k1/src/hash.h
        src/secp256k1/src/hash_impl.h
        src/secp256k1/src/num.h
        src/secp256k1/src/num_gmp.h
        src/secp256k1/src/num_gmp_impl.h
        src/secp256k1/src/num_impl.h
        src/secp256k1/src/scalar.h
        src/secp256k1/src/scalar_4x64.h
        src/secp256k1/src/scalar_4x64_impl.h
        src/secp256k1/src/scalar_8x32.h
        src/secp256k1/src/scalar_8x32_impl.h
        src/secp256k1/src/scalar_impl.h
        src/secp256k1/src/secp256k1.c
        src/secp256k1/src/testrand.h
        src/secp256k1/src/testrand_impl.h
        src/secp256k1/src/tests.c
        src/secp256k1/src/util.h
        src/support/allocators/secure.h
        src/support/allocators/zeroafterfree.h
        src/support/cleanse.cpp
        src/support/cleanse.h
        src/support/pagelocker.cpp
        src/support/pagelocker.h
        src/test/addrman_tests.cpp
        src/test/allocator_tests.cpp
        src/test/amount_tests.cpp
        src/test/arith_uint256_tests.cpp
        src/test/base32_tests.cpp
        src/test/base58_tests.cpp
        src/test/base64_tests.cpp
        src/test/bip32_tests.cpp
        src/test/blockencodings_tests.cpp
        src/test/bloom_tests.cpp
        src/test/Checkpoints_tests.cpp
        src/test/coins_tests.cpp
        src/test/compress_tests.cpp
        src/test/crypto_tests.cpp
        src/test/dbwrapper_tests.cpp
        src/test/DoS_tests.cpp
        src/test/getarg_tests.cpp
        src/test/hash_tests.cpp
        src/test/key_tests.cpp
        src/test/limitedmap_tests.cpp
        src/test/main_tests.cpp
        src/test/mempool_tests.cpp
        src/test/merkle_tests.cpp
        src/test/miner_tests.cpp
        src/test/multisig_tests.cpp
        src/test/net_tests.cpp
        src/test/netbase_tests.cpp
        src/test/pmt_tests.cpp
        src/test/policyestimator_tests.cpp
        src/test/pow_tests.cpp
        src/test/prevector_tests.cpp
        src/test/reverselock_tests.cpp
        src/test/rpc_tests.cpp
        src/test/sanity_tests.cpp
        src/test/scheduler_tests.cpp
        src/test/script_P2PKH_tests.cpp
        src/test/script_P2SH_tests.cpp
        src/test/script_tests.cpp
        src/test/scriptnum10.h
        src/test/scriptnum_tests.cpp
        src/test/serialize_tests.cpp
        src/test/sighash_tests.cpp
        src/test/sigopcount_tests.cpp
        src/test/skiplist_tests.cpp
        src/test/streams_tests.cpp
        src/test/test_softcoin.cpp
        src/test/test_softcoin.h
        src/test/testutil.cpp
        src/test/testutil.h
        src/test/timedata_tests.cpp
        src/test/transaction_tests.cpp
        src/test/txvalidationcache_tests.cpp
        src/test/uint256_tests.cpp
        src/test/univalue_tests.cpp
        src/test/util_tests.cpp
        src/test/versionbits_tests.cpp
        src/univalue/gen/gen.cpp
        src/univalue/include/univalue.h
        src/univalue/lib/univalue.cpp
        src/univalue/lib/univalue_escapes.h
        src/univalue/lib/univalue_read.cpp
        src/univalue/lib/univalue_utffilter.h
        src/univalue/lib/univalue_write.cpp
        src/univalue/test/unitester.cpp
        src/utils/dns_utils.cpp
        src/utils/dns_utils.h
        src/wallet/test/accounting_tests.cpp
        src/wallet/test/crypto_tests.cpp
        src/wallet/test/rpc_wallet_tests.cpp
        src/wallet/test/wallet_test_fixture.cpp
        src/wallet/test/wallet_test_fixture.h
        src/wallet/test/wallet_tests.cpp
        src/wallet/crypter.cpp
        src/wallet/crypter.h
        src/wallet/db.cpp
        src/wallet/db.h
        src/wallet/softnode.cpp
        src/wallet/softnode.h
        src/wallet/rpcdump.cpp
        src/wallet/rpcwallet.cpp
        src/wallet/rpcwallet.h
        src/wallet/wallet.cpp
        src/wallet/wallet.h
        src/wallet/walletdb.cpp
        src/wallet/walletdb.h
        src/zmq/zmqabstractnotifier.cpp
        src/zmq/zmqabstractnotifier.h
        src/zmq/zmqconfig.h
        src/zmq/zmqnotificationinterface.cpp
        src/zmq/zmqnotificationinterface.h
        src/zmq/zmqpublishnotifier.cpp
        src/zmq/zmqpublishnotifier.h
        src/addressindex.h
        src/addrman.cpp
        src/addrman.h
        src/aes_helper.c
        src/amount.cpp
        src/amount.h
        src/arith_uint256.cpp
        src/arith_uint256.h
        src/base58.cpp
        src/base58.h
        src/bignum.h
        src/blake.c
        src/blockencodings.cpp
        src/blockencodings.h
        src/bloom.cpp
        src/bloom.h
        src/bmw.c
        src/chain.cpp
        src/chain.h
        src/chainparams.cpp
        src/chainparams.h
        src/chainparamsbase.cpp
        src/chainparamsbase.h
        src/chainparamsseeds.h
        src/checkpoints.cpp
        src/checkpoints.h
        src/checkqueue.h
        src/clientversion.cpp
        src/clientversion.h
        src/coincontrol.h
        src/coins.cpp
        src/coins.h
        src/compat.h
        src/compressor.cpp
        src/compressor.h
        src/core_io.h
        src/core_memusage.h
        src/core_read.cpp
        src/core_write.cpp
        src/cubehash.c
        src/dbwrapper.cpp
        src/dbwrapper.h
        src/echo.c
        src/fugue.c
        src/groestl.c
        src/hamsi.c
        src/hamsi_helper.c
        src/hash.cpp
        src/hash.h
        src/hashblock.h
        src/httprpc.cpp
        src/httprpc.h
        src/httpserver.cpp
        src/httpserver.h
        src/indirectmap.h
        src/init.cpp
        src/init.h
        src/jh.c
        src/keccak.c
        src/kernel.cpp
        src/kernel.h
        src/key.cpp
        src/key.h
        src/keystore.cpp
        src/keystore.h
        src/limitedmap.h
        src/luffa.c
        src/main.cpp
        src/main.h
        src/memusage.h
        src/merkleblock.cpp
        src/merkleblock.h
        src/miner.cpp
        src/miner.h
        src/softcoin-cli.cpp
        src/softcoin-tx.cpp
        src/softcoind.cpp
        src/net.cpp
        src/net.h
        src/netbase.cpp
        src/netbase.h
        src/noui.cpp
        src/noui.h
        src/pos.cpp
        src/pos.h
        src/pow.cpp
        src/pow.h
        src/prevector.h
        src/protocol.cpp
        src/protocol.h
        src/pubkey.cpp
        src/pubkey.h
        src/random.cpp
        src/random.h
        src/rest.cpp
        src/reverselock.h
        src/scheduler.cpp
        src/scheduler.h
        src/serialize.h
        src/shavite.c
        src/simd.c
        src/skein.c
        src/spentindex.h
        src/sph_blake.h
        src/sph_bmw.h
        src/sph_cubehash.h
        src/sph_echo.h
        src/sph_fugue.h
        src/sph_groestl.h
        src/sph_hamsi.h
        src/sph_jh.h
        src/sph_keccak.h
        src/sph_luffa.h
        src/sph_shavite.h
        src/sph_simd.h
        src/sph_skein.h
        src/sph_types.h
        src/streams.h
        src/sync.cpp
        src/sync.h
        src/threadsafety.h
        src/timedata.cpp
        src/timedata.h
        src/timestampindex.h
        src/tinyformat.h
        src/torcontrol.cpp
        src/torcontrol.h
        src/txdb.cpp
        src/txdb.h
        src/txmempool.cpp
        src/txmempool.h
        src/ui_interface.cpp
        src/ui_interface.h
        src/uint256.cpp
        src/uint256.h
        src/undo.h
        src/util.cpp
        src/util.h
        src/utilmoneystr.cpp
        src/utilmoneystr.h
        src/utilstrencodings.cpp
        src/utilstrencodings.h
        src/utiltime.cpp
        src/utiltime.h
        src/validationinterface.cpp
        src/validationinterface.h
        src/version.h
        src/versionbits.cpp
        src/versionbits.h)
