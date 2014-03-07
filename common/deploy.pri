

CONFIG(release, debug|release) {
	mac {
		PH_DEPLOY_TARGET = $${PH_DEPLOY_LOCATION}$${TARGET}_v$${VERSION}.dmg

        !exists(/usr/local/bin/appdmg) {
                error("You must install appdmg : https://github.com/LinusU/node-appdmg")
        }

		QMAKE_PRE_LINK += rm -f $${TARGET}.app/Contents/Resources/qt.conf;

		QMAKE_POST_LINK += macdeployqt $${TARGET}.app;

		QMAKE_POST_LINK += export PATH=/usr/local/bin:$$(PATH);
		QMAKE_POST_LINK += cp $${_PRO_FILE_PWD_}/../../data/img/dmg_bg.png .;
		QMAKE_POST_LINK += sed -e "s/@TARGET@/$${TARGET}/g" $${_PRO_FILE_PWD_}/../../common/appdmg.json > appdmg.json;
		QMAKE_POST_LINK += rm $${PH_DEPLOY_TARGET};
		QMAKE_POST_LINK += appdmg appdmg.json $${PH_DEPLOY_TARGET};
		QMAKE_POST_LINK += open $${PH_DEPLOY_TARGET};
	}
}

OTHER_FILES += \
    ../../common/appdmg.json
