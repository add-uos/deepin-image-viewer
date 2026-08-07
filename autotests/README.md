# deepin-image-viewer 单元测试 (autotests)

本目录由 `qt-autotest-generator` skill 生成，是 deepin-image-viewer 的 Google Test
单元测试套件。采用**独立 CMake 工程**，不依赖应用程序 CMakeLists 中 `add_subdirectory`，
因此无需拉入 Qt6 Quick/QML 全套工具链即可编译运行。

## 目录结构

```
autotests/
├── CMakeLists.txt          独立测试工程
├── main.cpp                gtest main（QApplication + 日志分类 + 单例清理）
├── run-ut.sh               一键构建/运行/覆盖率
├── 3rdparty/stub/          内置 stub-ext（不从网络下载）
├── report_generator/       报告生成器（HTML/CSV）
└── src/test_<class>.cpp    各类测试用例
```

## 依赖

* Qt6 (Core/Gui/Widgets/Test/Concurrent/DBus/PrintSupport/Svg)
* Dtk6 (Core/Widget/Gui)
* `deepin-ocr-plugin-manager`、`ncnn`、`opencv_mobile`（pkg-config）
* lcov（覆盖率，可选）

若上述开发包未在系统安装，可通过本地提取的 prefix 提供（见 `run-ut.sh`）。

## 运行

```bash
./run-ut.sh            # 构建 + 运行 + 覆盖率
./run-ut.sh --no-cov   # 不生成覆盖率
```

## 覆盖率

测试运行在私有 D-Bus 会话中（`dbus-run-session`），保证 DBus 相关用例通过。
覆盖率基线（函数覆盖率）见 `report/` 下 HTML 报告。

## 说明

* 4 个强依赖 Qt Quick/QML 的类（`MouseTrackItem`、`PathViewRangeHandler`、
  `ImageProvider`、`LiveTextAnalyzer`）需 Quick/QML 工具链；如已安装相应开发包，
  将其在 `CMakeLists.txt` 的排除列表与 `src/` 测试中启用即可纳入。
* 测试不修改用户源码；疑似源码缺陷在测试注释或报告中标注。
