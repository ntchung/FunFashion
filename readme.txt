Setup Eclipse to work with NDK
==============================
1. Windows -> Preferences -> Android -> NDK -> Set Android NDK location...
2. File -> New -> Other -> C/C++ -> Convert to C/C++ project.

Common mistakes
===============
1. Could not find module... Forgot to set NDK_MODULE_PATH
=> In project Android.mk, add line $(call import-add-path, ..) ; make sure the path is correct and relative to project directory (not the jni directory).

2. No rule to make target... eventhough the paths seem correct
=> Previously built files were from different directory. Delete all old "obj" files.
