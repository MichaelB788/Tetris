add_library(TetrisCore
  Matrix.cpp
  NextQueue.cpp
  Playfield.cpp
  Tetris.cpp
  TetrisApp.cpp
  Tetromino.cpp
  srs.cpp
)
add_library(Tetris::Core ALIAS TetrisCore)

target_link_libraries(TetrisCore PUBLIC
  Tetris::Utils
)
