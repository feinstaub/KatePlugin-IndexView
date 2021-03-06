# Because the only official example CMake config I found was pretty outdated
# from 2004, https://kate-editor.org/2004/01/06/writing-a-kate-plugin/
# I like to thank Tatsh, https://github.com/Tatsh/kate-wakatime, where I could
# crib what to remove from the orig Kate main CMake file

project(kate-plugin-index-view)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(QT_MIN_VERSION "5.4.0")
set(KF5_DEP_VERSION "5.13.0")

find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets)
# find_package(KF5TextEditor NO_MODULE)
find_package(KF5 "${KF5_DEP_VERSION}" REQUIRED COMPONENTS
# Not sure if something is missed or could be removed
    Config
    I18n
    TextEditor
    XmlGui
)

# tell about our features (and what is missing)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

include(ECMOptionalAddSubdirectory)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(FeatureSummary)

# Sane flags from Kate project
add_definitions(
  -DQT_USE_QSTRINGBUILDER
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_CAST_FROM_ASCII
  -DQT_STRICT_ITERATORS
  -DQT_NO_URL_CAST_FROM_STRING
  -DQT_NO_CAST_FROM_BYTEARRAY
  -DQT_NO_SIGNALS_SLOTS_KEYWORDS
#   -DQT_USE_FAST_OPERATOR_PLUS
)

# Needed to find the moc file
include_directories(${CMAKE_CURRENT_BINARY_DIR})

ecm_optional_add_subdirectory(index-view)


# kate: space-indent on; indent-width 4; replace-tabs on;
