log(){
    local message="$1"
    current_time=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[${current_time}] $message"
}
CUR_DIR=$PWD
DS_VER=6.3
NTHREAD=4

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/nvidia/deepstream/deepstream-6.3/lib
LIB_DIR="/opt/nvidia/deepstream/deepstream-6.3"
LIB_DIR1="/opt/nvidia/deepstream/deepstream/lib/gst-plugins"

log "[INFO]backing up original files"
if [ -d "$LIB_DIR/backup" ]; then
  log "[INFO]dir already exists"
else
  log "[INFO]making backup dir"
  mkdir $LIB_DIR/backup
fi


FILE_NAME="gst-nvdscustomevent.h"
if [ ! -f "$LIB_DIR/backup/$FILE_NAME" ]; then
    log "[INFO]backup $FILE_NAME"
    cp $LIB_DIR/sources/includes/$FILE_NAME $LIB_DIR/backup
else
    log "[INFO]$FILE_NAME already backup"
fi

FILE_NAME="nvds_appctx_server.h"
if [ ! -f "$LIB_DIR/backup/$FILE_NAME" ]; then
    log "[INFO]backup $FILE_NAME"
    cp $LIB_DIR/sources/includes/$FILE_NAME $LIB_DIR/backup
else
    log "[INFO]$FILE_NAME already backup"
fi

FILE_NAME="nvds_rest_server.h"
if [ ! -f "$LIB_DIR/backup/$FILE_NAME" ]; then
    log "[INFO]backup $FILE_NAME"
    cp $LIB_DIR/sources/includes/$FILE_NAME $LIB_DIR/backup
else
    log "[INFO]$FILE_NAME already backup"
fi


LIB_NAME="libnvdsgst_customhelper.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]backup $LIB_NAME"
    cp $LIB_DIR/lib/$LIB_NAME $LIB_DIR/backup
    cp -r $LIB_DIR/sources/libs/gstnvdscustomhelper  $LIB_DIR/backup
else
    log "[INFO]$LIB_NAME already backup"
fi


LIB_NAME="libnvds_rest_server.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]backup $LIB_NAME"
    cp $LIB_DIR/lib/$LIB_NAME $LIB_DIR/backup
    cp -r $LIB_DIR/sources/libs/nvds_rest_server $LIB_DIR/backup
else
    log "[INFO]$LIB_NAME already backup"
fi


LIB_NAME="libnvds_dsanalytics.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]backup $LIB_NAME"
    cp $LIB_DIR/lib/$LIB_NAME $LIB_DIR/backup
    cp -r $LIB_DIR/sources/gst-plugins/gst-nvdsanalytics  $LIB_DIR/backup
else
    log "[INFO]$LIB_NAME already backup"
fi



LIB_NAME="libnvdsgst_nvmultiurisrcbin.so"
if [ ! -f "$LIB_DIR/backup/$LIB_NAME" ]; then
    log "[INFO]backup $LIB_NAME"
    cp $LIB_DIR1/$LIB_NAME $LIB_DIR/backup
    cp -r $LIB_DIR/sources/gst-plugins/gst-nvmultiurisrcbin  $LIB_DIR/backup
else
    log "[INFO]$LIB_NAME already backup"
fi






cuda_version=$(nvcc --version | grep -oP 'V\K\d+\.\d+')
log "[INFO]CUDA Version: $cuda_version"

export CUDA_VER=$cuda_version

log '[INFO]Installing dependencies'
cp $CUR_DIR/nvds_appctx_server.h $LIB_DIR/sources/includes

LIB_NAME="gstnvdscustomhelper"
log '[INFO]Building $LIB_NAME'
cp -r $CUR_DIR/$LIB_NAME $LIB_DIR/sources/libs   
cd $LIB_DIR/sources/libs/$LIB_NAME
make -j$NTHREAD
make install
cp gst-nvdscustomevent.h $LIB_DIR/sources/includes

LIB_NAME="nvds_rest_server"
log '[INFO]Building $LIB_NAME'
cp -r $CUR_DIR/$LIB_NAME $LIB_DIR/sources/libs
cd $LIB_DIR/sources/libs/$LIB_NAME
make -j$NTHREAD
make install
cp nvds_rest_server.h  $LIB_DIR/sources/includes 

cp  $CUR_DIR/nvds_appctx_server.h   $LIB_DIR/sources/includes
LIB_NAME="gst-nvmultiurisrcbin"
log '[INFO]Building $LIB_NAME'
cp -r $CUR_DIR/$LIB_NAME $LIB_DIR/sources/gst-plugins
cd $LIB_DIR/sources/gst-plugins/$LIB_NAME
make -j$NTHREAD
make install

LIB_NAME="gst-nvdsanalytics"
log '[INFO]Building $LIB_NAME'
cp -r $CUR_DIR/$LIB_NAME $LIB_DIR/sources/gst-plugins
cd $LIB_DIR/sources/gst-plugins/$LIB_NAME
make -j$NTHREAD
make install

LIB_NAME="deepstream-server-analytics"
#cp -r  $CUR_DIR/$LIB_NAME  $LIB_DIR/sources/apps/sample_apps
cp -r  $CUR_DIR/$LIB_NAME/config_nvdsanalytics.txt   $LIB_DIR/samples/configs/deepstream-app
cp -r  $CUR_DIR/config_test.txt    $LIB_DIR/samples/configs/deepstream-app
#cd  $LIB_DIR/sources/apps/sample_apps/$LIB_NAME
cd  $LIB_DIR/sources/apps/sample_apps/deepstream-app
make
#./deepstream-server-app dsserver_config.yml
./deepstream-app   -c $LIB_DIR/samples/configs/deepstream-app/config_test.txt

log "[SUCCESS]install success"
