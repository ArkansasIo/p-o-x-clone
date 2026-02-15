# Subsystem Configuration Files

You can create additional config files for each subsystem as needed. Example files:

- `config/audio.cfg`
- `config/video.cfg`
- `config/controls.cfg`
- `config/network.cfg`

Each file uses the same format as `game.cfg`.

Example `audio.cfg`:

```
master_volume float 0.8
music_volume float 0.6
sfx_volume float 0.7
mute bool false
```

Example `video.cfg`:
```
resolution string 1280x720
fullscreen bool true
vsync bool true
```

Example `controls.cfg`:
```
move_up string W
move_down string S
move_left string A
move_right string D
action string Space
```

Example `network.cfg`:
```
server_ip string 127.0.0.1
server_port int 12345
enable_multiplayer bool true
```
