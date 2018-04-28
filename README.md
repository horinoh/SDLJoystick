# SDLJoystick

* SDL
    * https://www.libsdl.org/index.php
    * Development Libraries を DL して適当な場所に解凍し、そこを指すように環境変数 SDL_SDK_PATH を作った

* SDL.prop
    * C/C++ - 追加のインクルードディレクトリ - 全般
    ~~~
    $(SDL_SDK_PATH)\include
    ~~~

    * リンカー - 全般 - 追加のライブラリディレクトリ
    ~~~
    $(SDL_SDK_PATH)\lib\x64
    ~~~