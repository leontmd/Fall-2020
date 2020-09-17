#include "gameplay.h"
#include "main_menu.h"
#include "object_def.h"
#include "pyinqt.h"
#include "tile.h"
#include "win_menu.h"
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>

gameplay::gameplay(engine& eng, int level)

    : _engine{eng}, _level(0), _current_level(level), _level_won(false),
      _text_handle(_engine.add_event_listener(
              sf::Event::TextEntered,
              [this](auto e) {
                  // for some reason saving/loading sends these events
                  if (e.text.unicode == 19 || e.text.unicode == 15) {
                      return false;
                  }
                  _input_con.handleEvents(
                          _text_doc, _text_view, _engine.window(), e);
                  return true;
              })),

      _pressed_handle(_engine.add_event_listener(
              sf::Event::KeyPressed,
              [this](auto e) {
                  if (_handle_keyboard(e)) {
                      return true;
                  } else if (e.key.code == sf::Keyboard::Escape) {
                      _to_state = std::make_unique<main_menu>(_engine);
                      return true;
                  } else {
                      _input_con.handleEvents(
                              _text_doc, _text_view, _engine.window(), e);
                      return true;
                  }
                  return false;
              })),

      _released_handle(_engine.add_event_listener(
              sf::Event::KeyReleased,
              [this](auto e) {
                  if (e.key.code == sf::Keyboard::Escape) {
                      _to_state = std::make_unique<main_menu>(_engine);
                      return true;
                  } else {
                      _input_con.handleEvents(
                              _text_doc, _text_view, _engine.window(), e);
                      return true;
                  }
                  return false;
              })),

      _mouse_click(_engine.add_event_listener(
              sf::Event::MouseButtonPressed,
              [this](auto e) {
                  _input_con.handleEvents(
                          _text_doc, _text_view, _engine.window(), e);
                  return true;
              })),

      _text_view((_editor_subtarget.create(1920 * 0.333333, 1080),
                  _editor_subtarget),
                 "./../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf"),
      _stdout_lines(12) {
    _load_level(_current_level);
    _text_doc.addTextToPos(_level._level_instructions, 0, 0);
    int lines = _text_doc.getLineCount();
    for (int i = 0; i < lines; i++) {
        _text_view.moveCursorDown(_text_doc, false);
    }
    _text_view.moveCursorToEnd(_text_doc, false);

    _error_console.setSize(sf::Vector2f(600, 250));
    _error_console.setFillColor(sf::Color(95, 95, 95)); // Error console output
    _error_console.setOrigin(_error_console.getSize().x,
                             _error_console.getSize().y);
    _error_console.setPosition(.666 * _engine.window().getSize().x,
                               _engine.window().getSize().y);
}

std::unique_ptr<game_state> gameplay::update() {
    _engine.window().clear(sf::Color(252, 252, 210)); // Background to map

    // Draw tiles
    for (int i = 0; i < _level.get_location_matrix().shape()[0]; i++) {
        for (int j = 0; j < _level.get_location_matrix().shape()[1]; j++) {
            tile tile_to_draw = _level.get_location_tile_def(i, j);
            tile_to_draw.set_sprite_position(
                    j * 64 + (.1655 * _engine.window().getSize().x),
                    i * 64 + (.1665 * _engine.window().getSize().y));
            _engine.window().draw((tile_to_draw.get_sprite()));

            // Check for tank off of road
            if (tile_to_draw.get_type() != "road") {
                if (((_tank->get_position().x) - 32 + 2 >=
                             tile_to_draw.get_sprite().getPosition().x &&
                     (_tank->get_position().x) - 32 - 2 <=
                             tile_to_draw.get_sprite().getPosition().x) &&
                    ((_tank->get_position().y) - 32 + 2 >=
                             tile_to_draw.get_sprite().getPosition().y &&
                     (_tank->get_position().y) - 32 - 2 <=
                             tile_to_draw.get_sprite().getPosition().y)) {

                    // Explode tank
                    if (_tank->done_exploding()) {
                        _load_level(_current_level);
                        return nullptr;
                    } else {
                        _tank->run_state(std::make_unique<tank::explode>());
                    }
                }
            }
        }
    }

    // Draw objects
    _tank->update();
    for (int i = 0; i < _objects.size(); i++) {
        _engine.window().draw(_objects[i]->get_sprite());

        // Tank out of bounds check
        if (_tank->get_position().x < .1655 * _engine.window().getSize().x ||
            _tank->get_position().x >
                    (.1655 * _engine.window().getSize().x +
                     _level.get_location_matrix().shape()[1] * 64) ||
            _tank->get_position().y < .1655 * _engine.window().getSize().y ||
            _tank->get_position().y >
                    (.1655 * _engine.window().getSize().y +
                     _level.get_location_matrix().shape()[0] * 64)) {
            // Explode tank
            if (_tank->done_exploding()) {
                _load_level(_current_level);
                return nullptr;
            } else {
                _tank->run_state(std::make_unique<tank::explode>());
            }
        }

        // Tank hitting objects check
        if (_objects[i]->get_type() != "spawn") {
            if (_objects[i]->get_position().x - _objects[i]->get_size().x <
                _tank->get_position().x) {
                if (_objects[i]->get_position().x + _objects[i]->get_size().x >
                    _tank->get_position().x) {
                    if (_objects[i]->get_position().y -
                                _objects[i]->get_size().y <
                        _tank->get_position().y) {
                        if (_objects[i]->get_position().y +
                                    _objects[i]->get_size().y >
                            _tank->get_position().y) {
                            if (_objects[i]->get_type() == "goal") {
                                _level_won = true;
                            } else {
                                if (_tank->done_exploding()) {
                                    _load_level(_current_level);
                                    return nullptr;
                                } else {
                                    _tank->run_state(
                                            std::make_unique<tank::explode>());
                                }
                            }
                        }
                    }
                }
            }
        }

        // Hit detection for objects and bullet
        if (_tank->is_shooting()) {
            if (_objects[i]->get_type() == "destroyable" ||
                _objects[i]->get_type() == "solid") {
                if (_objects[i]->get_position().x - _objects[i]->get_size().x <
                    _tank->get_bullet_pos().x) {
                    if (_objects[i]->get_position().x +
                                _objects[i]->get_size().x >
                        _tank->get_bullet_pos().x) {
                        if (_objects[i]->get_position().y -
                                    _objects[i]->get_size().y <
                            _tank->get_bullet_pos().y) {

                            if (_objects[i]->get_position().y +
                                        _objects[i]->get_size().y >
                                _tank->get_bullet_pos().y) {
                                _tank->bullet_hit();
                                if (_objects[i]->get_type() == "destroyable") {
                                    _objects.erase(_objects.begin() + i);
                                    i = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    _engine.window().draw(*_tank);
    _editor_subtarget.clear(sf::Color(238, 228, 196)); // Editor background
    _editor_subtarget.setView(_text_view.getCameraView());
    if (auto l = _executing_line.load(); l > 0) {
        auto to_highlight = sf::RectangleShape(sf::Vector2f(
                _editor_subtarget.getSize().x, _text_view.getLineHeight()));
        to_highlight.setPosition(0, _text_view.lineY(l));
        to_highlight.setFillColor(
                sf::Color(201, 187, 143)); // Editor step through highlight
        _editor_subtarget.draw(to_highlight);
    }
    _text_view.draw(_editor_subtarget, _text_doc);
    auto editor = sf::Sprite();
    editor.setPosition(0.66666 * _engine.window().getSize().x, 0);
    _editor_subtarget.display();
    editor.setTexture(_editor_subtarget.getTexture());
    _engine.window().draw(editor);

    // draw level name
    auto level_name = sf::Text();
    auto font = sf::Font();
    font.loadFromFile(
            "../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
    auto level_font = sf::Font();
    level_font.loadFromFile(
            "../team-triangle-eduapp/assets/fonts/Minecraft.ttf");
    level_name.setString(_level._level_name);
    level_name.setPosition(0.1665 * _engine.window().getSize().x, 10);
    level_name.setCharacterSize(50);
    level_name.setFont(level_font);
    level_name.setFillColor(sf::Color(36, 156, 11));
    _engine.window().draw(level_name);

    // draw stdout

    auto s = std::string();
    {
        auto lock = std::lock_guard(_pyout_mutex);
        while (std::getline(_pyout, s)) {
            _stdout_lines.push_back(s);
        }
        _pyout.clear();
    }

    // draw error console
    _engine.window().draw(_error_console);
    auto error_title = sf::RectangleShape();
    error_title.setSize(sf::Vector2f(_error_console.getSize().x, 30));
    error_title.setOrigin(error_title.getSize().x, 0);
    error_title.setPosition(.666 * _engine.window().getSize().x,
                            _engine.window().getSize().y -
                                    _error_console.getSize().y);
    error_title.setFillColor(sf::Color(80, 80, 80)); // Error title
    _engine.window().draw(error_title);

    auto error_title_text = sf::Text();
    error_title_text.setFont(font);
    error_title_text.setFillColor(sf::Color::White);
    error_title_text.setPosition(
            .666 * _engine.window().getSize().x - _error_console.getSize().x,
            _engine.window().getSize().y - _error_console.getSize().y);
    error_title_text.setCharacterSize(14);
    error_title_text.setString("Error Console");
    _engine.window().draw(error_title_text);

    // write errors
    auto stdout_str = std::string();
    for (const auto& s : _stdout_lines) {
        stdout_str += s + "\n";
    }
    auto stdout_text = sf::Text();
    stdout_text.setFont(font);
    stdout_text.setString(stdout_str);
    stdout_text.setFillColor(sf::Color::White);
    stdout_text.setPosition(.666 * _engine.window().getSize().x -
                                    _error_console.getSize().x + 5,
                            _engine.window().getSize().y -
                                    _error_console.getSize().y + 30);
    stdout_text.setCharacterSize(15);
    _engine.window().draw(stdout_text);

    if (_level_won) {
        _kill_sig = true;
        _tank->run_state(nullptr);
        _tank_controller->join();
        _to_state = std::make_unique<win_menu>(_engine, _current_level);
    }

    return std::move(_to_state);
}

// https://wiki.python.org/moin/boost.python/EmbeddingPython
std::string extract_exception() {
    using namespace boost::python;

    PyObject *exc, *val, *tb;
    PyErr_Fetch(&exc, &val, &tb);
    PyErr_NormalizeException(&exc, &val, &tb);
    handle<> hexc(exc), hval(allow_null(val)), htb(allow_null(tb));
    if (!hval) {
        return extract<std::string>(str(hexc));
    } else {
        object traceback(import("traceback"));
        object format_exception(traceback.attr("format_exception"));
        object formatted_list(format_exception(hexc, hval, htb));
        object formatted(str("").join(formatted_list));
        return extract<std::string>(formatted);
    }
}

boost::python::object traceit(const std::atomic<bool>& kill_sig,
                              std::atomic<int>& executing_line,
                              bool& killed,
                              boost::python::object f,
                              boost::python::object e,
                              boost::python::object a) {
    namespace py = boost::python;
    if (kill_sig) {
        killed = true;
        throw std::runtime_error("ExplosionError");
    }
    if (py::extract<std::string>(e)() == "line") {
        executing_line = py::extract<int>(f.attr("f_lineno"))();
    }
    return py::make_function(
            [&](boost::python::object f,
                boost::python::object e,
                boost::python::object a) {
                return traceit(kill_sig, executing_line, killed, f, e, a);
            },
            py::default_call_policies(),
            boost::mpl::
                    vector<py::object, py::object, py::object, py::object>());
}

bool gameplay::_run_tanks() {
    _load_level(_current_level);
    auto user_source = std::string();
    for (auto i = 0; i < _text_doc.getLineCount(); i++) {
        user_source.append(_text_doc.getLine(i).toAnsiString() + "\n");
    }
    _executing_line = 0;
    _kill_sig = false;
    _tank_controller = std::make_unique<std::thread>([this, user_source]() {
        namespace py = boost::python;
        // Retrieve the main module.
        auto killed = false;
        try {
            auto main = py::import("__main__");
            auto sys = py::import("sys");

            sys.attr("settrace")(py::make_function(
                    [this, &killed](py::object frame,
                                    py::object event,
                                    py::object args) {
                        return traceit(_kill_sig,
                                       _executing_line,
                                       killed,
                                       frame,
                                       event,
                                       args);
                    },
                    py::default_call_policies(),
                    boost::mpl::vector<py::object,
                                       py::object,
                                       py::object,
                                       py::object>()));
            // Retrieve the main module's namespace
            auto global = main.attr("__dict__");
            global["d_print"] = py::make_function(
                    std::function([this](py::object x) {
                        auto l = std::lock_guard(_pyout_mutex);
                        _pyout << py::extract<std::string>(
                                          x.attr("__str__")())()
                               << std::endl;
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void, py::object>());

            global["forward"] = py::make_function(
                    std::function([this]() {
                        _tank->run_state(std::make_unique<tank::move>(true));
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["backward"] = py::make_function(
                    std::function([this]() {
                        _tank->run_state(std::make_unique<tank::move>(false));
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["turn_left"] = py::make_function(
                    std::function([this]() {
                        _tank->run_state(std::make_unique<tank::rotate>(false));
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["turn_right"] = py::make_function(
                    std::function([this]() {
                        _tank->run_state(std::make_unique<tank::rotate>(true));
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["shoot"] = py::make_function(
                    std::function([this]() {
                        _tank->run_state(std::make_unique<tank::shoot>());
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void>());

            global["rotate_turret"] = py::make_function(
                    std::function([this](py::object py_angle) {
                        auto angle = py::extract<float>(py_angle);
                        _tank->run_state(
                                std::make_unique<tank::rot_turret>(angle));
                        _tank->wait_until_idle();
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<void, py::object>());
            global["object_ahead"] = py::make_function(
                    std::function([this]() -> py::object {
                        int x = ((_tank->get_position().x - 32) -
                                 (int)(.1655 * _engine.window().getSize().x)) /
                                64;
                        int y = ((_tank->get_position().y - 32) -
                                 (int)(.1655 * _engine.window().getSize().y)) /
                                64;

                        for (int i = 0; i < _objects.size(); i++) {
                            if (_objects[i]->get_type() == "destroyable" ||
                                _objects[i]->get_type() == "static") {
                                if (x + _tank->get_rotation_vector().x ==
                                            _objects[i]->get_location().x &&
                                    y + _tank->get_rotation_vector().y ==
                                            _objects[i]->get_location().y) {
                                    return py::object(true);
                                }
                            }
                        }
                        return py::object(false);
                    }),
                    py::default_call_policies(),
                    boost::mpl::vector<py::object>());

            auto result = py::exec(py::str(user_source), global, global);
        } catch (py::error_already_set const&) {
            if (!killed) {
                _pyout << extract_exception();
            }
        }
        _executing_line = 0;
    });
}

bool gameplay::_load_level(int level) {
    _level.load_new_level(level);
    _current_level = level;
    _kill_sig = true;
    if (_tank) {
        _tank->run_state(nullptr);
    }
    if (_tank_controller) {
        _tank_controller->join();
        _tank_controller = nullptr;
    }

    _objects.clear();
    _executing_line = 0;

    for (auto& obj : _level.get_objects()) {
        obj->set_offset(.1655 * _engine.window().getSize().x,
                        .1655 * _engine.window().getSize().y);
        _objects.emplace_back(obj);
        if (obj->get_type() == "spawn") {
            // Load Tank
            _tank = std::make_unique<tank>(
                    _engine,
                    sf::Sprite(_engine.load_texture(
                            "../team-triangle-eduapp/assets/Tanks/PNG/"
                            "DefaultSize/tankBody_blue.png")),
                    sf::Sprite(_engine.load_texture(
                            "../team-triangle-eduapp/assets/Tanks/PNG/"
                            "DefaultSize/tankBlue_barrel2_outline.png")),
                    sf::Sprite(_engine.load_texture(
                            "../team-triangle-eduapp/assets/Tanks/PNG/"
                            "DefaultSize/bulletBlue1_outline.png")));
            _tank->set_position(obj->get_position());
        }
    }

    _tank->set_bullet_bounds(
            .1655 * _engine.window().getSize().x,
            .1655 * _engine.window().getSize().y,
            .1655 * _engine.window().getSize().x +
                    (_level.get_location_matrix().shape()[1] * 64),
            .1655 * _engine.window().getSize().y +
                    (_level.get_location_matrix().shape()[0] * 64));

    return true;
}

bool gameplay::_handle_keyboard(sf::Event event) {
    if (event.key.code == sf::Keyboard::F5) {
        _run_tanks();
        return true;
    } else if (event.key.code == sf::Keyboard::O && event.key.control) {
        _text_doc.loadFile(QFileDialog::getOpenFileName().toStdString());
        _text_view = TextView(
                _editor_subtarget,
                "./../team-triangle-eduapp/assets/fonts/droid_sans_mono.ttf");
        return true;
    } else if (event.key.code == sf::Keyboard::S && event.key.control) {
        _text_doc.saveFile(QFileDialog::getSaveFileName().toStdString());
        return true;
    } else if (event.key.code == sf::Keyboard::Escape) {
        _kill_sig = true;
        _tank->run_state(nullptr);
        if (_tank_controller) {
            _tank_controller->join();
        }
        _to_state = std::make_unique<main_menu>(_engine);
        return true;
    } else {
        return false;
    }
}
