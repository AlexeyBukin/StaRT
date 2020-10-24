#!/bin/zsh

# Changing linking .dylibs on 42School MACs

OLD_IFS=$IFS
IFS=$'\n'

lib=RT
for file in $(otool -l $lib | grep KCHARLA | awk '{print $2}');
  do
    install_name_tool -change "$file" "@rpath/`echo $file | rev | cut -d/ -f 1 | rev`" $lib;
  done
install_name_tool -add_rpath "@executable_path/gtk_bundle_42/lib" $lib

IFS=$OLD_IFS

#for lib in $(ls -1 gtk_bundle_42/lib/*);
#do
##lib=RT
#  echo "$lib";
#  for file in $(otool -l $lib | grep KCHARLA | awk '{print $2}');
#  do
###    echo $file;
#    install_name_tool -change "$file" "@rpath/`echo $file | rev | cut -d/ -f 1 | rev`" $lib;
#  done
##  install_name_tool -add_rpath "." $lib;
#  echo "\n";
#done
#BINARY_TO_DO="RT"
#OTOOL_PATHS=$(otool -l $BINARY_TO_DO | grep KCHARLA | awk '{print $2}')
#for file in $(otool -l $BINARY_TO_DO | grep KCHARLA | awk '{print $2}');
#do
##  echo $file;
##  echo "`echo $file | rev | cut -d/ -f 1 | rev`";
#  install_name_tool -change "$file" "@rpath/`echo $file | rev | cut -d/ -f 1 | rev`" $BINARY_TO_DO;
##    echo $file;
##    echo $file | rev | cut -d/ -f 1 | rev ;
#done



