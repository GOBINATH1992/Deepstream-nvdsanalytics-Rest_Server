###
 # @Author: Gobinath
 # @Date: 2024-07-26 13:00:00
 # @Description: 
 # @LastEditors: Gobinath
 # @LastEditTime: 2024-07-26 13:00:00
### 

log() {
    local message="$1"
    current_time=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[${current_time}] $message"
    
}

CUR_DIR=$PWD
DS_VER=6.3
LIB_DIR="/opt/nvidia/deepstream/deepstream-6.3"
LIB_DIR1="/opt/nvidia/deepstream/deepstream/lib/gst-plugins"

log "[CHECK]check backup dir"
if [ ! -d "$LIB_DIR/backup" ]; then
  log "[INFO]no backup dir"
  exit 1
fi


FILE_NAME="gst-nvdscustomevent.h"

if [ ! -f "$LIB_DIR/backup/$FILE_NAME" ]; then
    log "[INFO]missing file gst-nvdscustomevent.h"
    exit 1
else
    log "[INFO]restore gst-nvdscustomevent.h"
    cp $LIB_DIR/backup/$FILE_NAME   $LIB_DIR/sources/includes 
fi



FILE_NAME="nvds_rest_server.h"
if [ ! -f "$LIB_DIR/backup/$FILE_NAME" ]; then
    log "[INFO]missing file nvds_rest_server.h"
    exit 1
else
    log "[INFO]restore nvds_rest_server.h"
    cp $LIB_DIR/backup/$FILE_NAME   $LIB_DIR/sources/includes 
fi



LIB_NAME="libnvdsgst_customhelper.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]missing file  libnvdsgst_customhelper.so "
    exit 1  
else
    log "[INFO]libnvdsgst_customhelper.so restore"
    cp  $LIB_DIR/backup/$LIB_NAME $LIB_DIR/lib 
    cp -r $LIB_DIR/backup/gstnvdscustomhelper   $LIB_DIR/sources/libs 
fi


LIB_NAME="libnvds_rest_server.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO] missing file libnvds_rest_server.so"
    exit 1  
    
else
    
    cp $LIB_DIR/backup/$LIB_NAME $LIB_DIR/lib 
    cp -r $LIB_DIR/backup/nvds_rest_server $LIB_DIR/sources/libs
    cd  
    log "[INFO]libnvds_rest_server.so restore"
    
fi


LIB_NAME="libnvds_dsanalytics.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]missing file libnvds_dsanalytics.so"
    exit 1  
    
else
    
    cp $LIB_DIR/backup/$LIB_NAME $LIB_DIR/lib 
    cp -r  $LIB_DIR/backup/gst-nvdsanalytics  $LIB_DIR/sources/gst-plugins  
    log "[INFO]libnvds_dsanalytics.s restore"
fi



LIB_NAME="libnvdsgst_nvmultiurisrcbin.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]missing file libnvdsgst_nvmultiurisrcbin.so"
    exit 1  
else
    cp  $LIB_DIR/backup/$LIB_NAME  $LIB_DIR1
    cp -r $LIB_DIR/backup/gst-nvmultiurisrcbin $LIB_DIR/sources/gst-plugins  
    log "[INFO]libnvdsgst_nvmultiurisrcbin.so restore"
fi

cuda_version=$(nvcc --version | grep -oP 'V\K\d+\.\d+')
log "[INFO]CUDA Version: $cuda_version"

export CUDA_VER=$cuda_version

log '[INFO]ReInstalling dependencies'

LIB_NAME="gstnvdscustomhelper"
log '[INFO]Building $LIB_NAME' 
cd $LIB_DIR/sources/libs/$LIB_NAME
make -j$NTHREAD
make install


LIB_NAME="nvds_rest_server"
log '[INFO]Building $LIB_NAME'
cd $LIB_DIR/sources/libs/$LIB_NAME
make -j$NTHREAD
make install



LIB_NAME="gst-nvmultiurisrcbin"
log '[INFO]Building $LIB_NAME'
cd $LIB_DIR/sources/gst-plugins/$LIB_NAME
make -j$NTHREAD
make install

LIB_NAME="gst-nvdsanalytics"
log '[INFO]Building $LIB_NAME'
cd $LIB_DIR/sources/gst-plugins/$LIB_NAME
make -j$NTHREAD
make install






log "[SUCCESS]restore success"
