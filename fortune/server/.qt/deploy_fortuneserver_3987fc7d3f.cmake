include(/Users/jiyongso/development/Qt/fortune/server/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/fortuneserver-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE fortuneserver.app
)
