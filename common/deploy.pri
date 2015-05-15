win32 {
	QMAKE_POST_LINK += windeployqt $${RESOURCES_PATH} $${CS}
}

mac {
	app_bundle {
		QMAKE_POST_LINK += echo Create Info.plist;
		QMAKE_POST_LINK += cp $$(QTDIR)/mkspecs/macx-clang/Info.plist.app $${TARGET}.app/Contents/Info.plist;

		QMAKE_POST_LINK += plutil -replace CFBundleExecutable -string $${TARGET} $${TARGET}.app/Contents/Info.plist;

		!defined(ICON) ICON = $$TOP_ROOT/data/icon.icns
		QMAKE_POST_LINK += cp $$ICON $${TARGET}.app/Contents/Resources/$${TARGET}.icns;
		QMAKE_POST_LINK += plutil -replace CFBundleIconFile -string $${TARGET}.icns $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -replace CFBundleIdentifier -string com.phonations.$${TARGET} $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -replace CFBundleSignature -string ??? $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -insert CFBundleVersion -string $${VERSION} $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -insert NSPrincipalClass -string NSApplication $${TARGET}.app/Contents/Info.plist;
		QMAKE_POST_LINK += plutil -insert NSHighResolutionCapable -string True $${TARGET}.app/Contents/Info.plist;
	}
}

CONFIG(release, debug|release) {
	mac {
		app_bundle {
			PH_DEPLOY_TARGET = $${TARGET}_v$${VERSION}.dmg
			message($$PH_DEPLOY_TARGET)

			QMAKE_POST_LINK += macdeployqt $${TARGET}.app;

##################################################

			# creating dmg with create-dmg

			QMAKE_POST_LINK += $${_PRO_FILE_PWD_}/../../vendor/create-dmg/create-dmg \
				--volname $${TARGET}_v$${VERSION} \
				--background $${_PRO_FILE_PWD_}/../../data/img/dmg_bg.png \
				--app-drop-link 450 218 \
				--icon $${TARGET}.app 150 218 \
				--window-size 600 450 \
				$${PH_DEPLOY_TARGET} \
				$${TARGET}.app;

			QMAKE_POST_LINK += cp $${PH_DEPLOY_TARGET} $${PH_DEPLOY_LOCATION};
		}
	}

	win32 {
		QMAKE_POST_LINK += echo "Deploying Joker" $${CS}
		QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_path($${TOP_ROOT}/app/Joker/JokerSetup.iss) . $${CS}
		QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_path($${TOP_ROOT}/LICENSE.TXT) . $${CS}
		QMAKE_POST_LINK += ISCC.exe JokerSetup.iss $${CS}
	}
}
