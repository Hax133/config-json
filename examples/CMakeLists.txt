build_lib_example(
  NAME config-json-example
  SOURCE_FILES config-json-example.cc
  LIBRARIES_TO_LINK 
    ${libcore}
    ${libnetwork}
    ${libpoint-to-point}
    ${libwifi}
    ${libcsma}
    ${libbridge}
    ${libinternet}
    ${libolsr}
    ${libmobility}
    ${libapplications}
    ${libflow-monitor}
    ${libconfig-json}
)