CXX=g++
SDKROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk
CFLAGS=-std=c++17 -stdlib=libc++ -Ofast -march=native -flto -fno-signed-zeros -fno-trapping-math -funroll-loops -Wno-deprecated -I/usr/local/include -I. -Isrc/ -Ithird_party -isysroot $(SDKROOT)
LDFLAGS=-Wl,-search_paths_first -Wl,-headerpad_max_install_names -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo -framework CoreFoundation -lraylib -Lthird_party/raylib/
EXEC=main

all: Rectangle.o sprite_rect_buffer.o position.o entity.o entity_factory.o ship.o ship_state_transitions.o fuel_tank.o radar_tower.o gun_ver.o gun_hor_north.o gun_hor_south.o parked_plane.o laser_bolt_green.o enemy_rune.o ship_shadow.o main_menu_screen.o state_machine.o game_manager.o sprite.o entity_sprite_sheet_animation.o entity_sprite_sheet.o entity_data_manager.o
	$(CXX) $(CFLAGS) $(LDFLAGS) main.cpp entity.o entity_factory.o ship.o ship_state_transitions.o fuel_tank.o radar_tower.o gun_ver.o gun_hor_north.o gun_hor_south.o parked_plane.o laser_bolt_green.o enemy_rune.o ship_shadow.o main_menu_screen.o state_machine.o game_manager.o sprite.o entity_data_manager.o entity_sprite_sheet.o entity_sprite_sheet_animation.o position.o sprite_rect_buffer.o Rectangle.o -o $(EXEC)

ship.o: src/entities/ship.cpp
	$(CXX) -c $(CFLAGS) src/entities/ship.cpp

ship_state_transitions.o: src/entities/ship_state_transitions.cpp
	$(CXX) -c $(CFLAGS) src/entities/ship_state_transitions.cpp

fuel_tank.o: src/entities/fuel_tank.cpp
	$(CXX) -c $(CFLAGS) src/entities/fuel_tank.cpp

radar_tower.o: src/entities/radar_tower.cpp
	$(CXX) -c $(CFLAGS) src/entities/radar_tower.cpp

gun_ver.o: src/entities/gun_ver.cpp
	$(CXX) -c $(CFLAGS) src/entities/gun_ver.cpp

gun_hor_north.o: src/entities/gun_hor_north.cpp
	$(CXX) -c $(CFLAGS) src/entities/gun_hor_north.cpp

gun_hor_south.o: src/entities/gun_hor_south.cpp
	$(CXX) -c $(CFLAGS) src/entities/gun_hor_south.cpp

parked_plane.o: src/entities/parked_plane.cpp
	$(CXX) -c $(CFLAGS) src/entities/parked_plane.cpp

laser_bolt_green.o: src/entities/laser_bolt_green.cpp
	$(CXX) -c $(CFLAGS) src/entities/laser_bolt_green.cpp

enemy_rune.o: src/entities/enemy_rune.cpp
	$(CXX) -c $(CFLAGS) src/entities/enemy_rune.cpp

ship_shadow.o: src/entities/ship_shadow.cpp
	$(CXX) -c $(CFLAGS) src/entities/ship_shadow.cpp

main_menu_screen.o: src/main_menu_screen.cpp
	$(CXX) -c $(CFLAGS) src/main_menu_screen.cpp

state_machine.o: src/state_machine.cpp
	$(CXX) -c $(CFLAGS) src/state_machine.cpp

entity_factory.o: src/entity_factory.cpp
	$(CXX) -c $(CFLAGS) src/entity_factory.cpp

entity_data_manager.o: src/entity_data_manager.cpp
	$(CXX) -c $(CFLAGS) src/entity_data_manager.cpp

game_manager.o: src/game_manager.cpp
	$(CXX) -c $(CFLAGS) src/game_manager.cpp

entity.o: src/entity.cpp
	$(CXX) -c $(CFLAGS) src/entity.cpp

entity_sprite_sheet.o: src/entity_sprite_sheet.cpp
	$(CXX) -c $(CFLAGS) src/entity_sprite_sheet.cpp

entity_sprite_sheet_animation.o: src/entity_sprite_sheet_animation.cpp
	$(CXX) -c $(CFLAGS) src/entity_sprite_sheet_animation.cpp

sprite.o: src/sprite.cpp
	$(CXX) -c $(CFLAGS) src/sprite.cpp

position.o: src/position.cpp
	$(CXX) -c $(CFLAGS) src/position.cpp

sprite_rect_buffer.o: src/sprite_rect_buffer.cpp
	$(CXX) -c $(CFLAGS) src/sprite_rect_buffer.cpp

Rectangle.o: src/collision/geometry/Rectangle.cpp
	$(CXX) -c $(CFLAGS) src/collision/geometry/Rectangle.cpp

clean:
	rm -f $(EXEC) *.o *.gch src/*.o src/*.gch third_party/collision/structures/*.gch
