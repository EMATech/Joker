win32 {
	QMAKE_POST_LINK += windeployqt $${RESOURCES_PATH} $${CS}
}

mac {
	app_bundle {
		QMAKE_POST_LINK += plutil -replace CFBundleIdentifier -string com.phonations.$$lower($${TARGET}) $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -replace CFBundleVersion -string $${VERSION} $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -replace CFBundleShortVersionString -string $${VERSION} $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -insert LSApplicationCategoryType -string public.app-category.video $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -replace NSHighResolutionCapable -string True $${TARGET}.app/Contents/Info.plist;

		removeapp.commands += rm -rf $${TARGET}.app

		QMAKE_EXTRA_TARGETS += removeapp
	}
}

CONFIG(release, debug|release) {
	mac {
		app_bundle {
			QMAKE_POST_LINK += codesign -s $$(APPLICATION_CERTIFICATE) -v --entitlements $$TOP_ROOT/common/entitlements.plist $${TARGET}.app;

			QMAKE_POST_LINK += macdeployqt $${TARGET}.app -always-overwrite -codesign=$$(APPLICATION_CERTIFICATE);

			if(equals(PH_GIT_BRANCH, "master") || equals(PH_GIT_BRANCH, "HEAD")) {
				PH_DEPLOY_TARGET = $${TARGET}_v$${VERSION}
			} else {
				PH_DEPLOY_TARGET = $${TARGET}_v$${VERSION}_$${PH_GIT_BRANCH}
			}

			message($$PH_DEPLOY_TARGET)

			QMAKE_POST_LINK += echo "Build PKG";

			QMAKE_POST_LINK += echo $$(INSTALLER_CERTIFICATE);
			QMAKE_POST_LINK += productbuild --component $${TARGET}.app /Applications --sign $$(INSTALLER_CERTIFICATE) $${PH_DEPLOY_TARGET}.pkg;

			QMAKE_POST_LINK += cp $${PH_DEPLOY_TARGET}.pkg $${PH_DEPLOY_LOCATION};

			installer.commands += echo "Generate $$PH_DEPLOY_TARGET:";
			installer.commands += $${_PRO_FILE_PWD_}/../../vendor/create-dmg/create-dmg \
					--volname $${PH_DEPLOY_TARGET} \
#					--volicon $${_PRO_FILE_PWD_}/../../app/Joker/joker.icns \
					--background $${_PRO_FILE_PWD_}/../../data/img/dmg_bg.png \
					--app-drop-link 450 218 \
					--icon $${TARGET}.app 150 218 \
					--window-size 600 450 \
					$${PH_DEPLOY_TARGET}.dmg \
					$${TARGET}.app &&
			installer.commands += cp $${PH_DEPLOY_TARGET}.dmg $${PH_DEPLOY_LOCATION}

			removedmg.commands += rm $${PH_DEPLOY_TARGET}.dmg

			QMAKE_EXTRA_TARGETS += removedmg
		}
	}

	win32 {
		if(exists($${_PRO_FILE_PWD_}/$$TARGET.iss)) {
			installer.commands += echo "Running Innosetup on $${_PRO_FILE_PWD_}/$${TARGET}.iss" &
			installer.commands += iscc $${_PRO_FILE_PWD_}/$${TARGET}.iss /DPWD=$$OUT_PWD
		}
	}
}

QMAKE_EXTRA_TARGETS += installer
