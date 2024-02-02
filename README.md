<h1 align="center">
cub3D
</h1>
<p align="center">
💥 RayCaster with miniLibX 💥
</p>

A “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective created using 
the Ray-Casting principles.

## Usage
cub3D uses the [miniLibX](https://github.com/42Paris/minilibx-linux) library

**Clone the Repository**
  ```shell
  git clone git@github.com:EstebanFlorence/cub3D.git
  cd cub3D
  ```

 **Compile on Linux**
  ```shell
  make
  ```
 **Compile on MacOS**
  ```shell
  make mac
  ```
  **Run**
  ```shell
  ./cub3D file.cub
  ```

NB  .cub files must be located in maps/



<div align="center">
<img width="796" alt="Screenshot" src="https://github.com/EstebanFlorence/cub3D/assets/77881363/ad528e33-6307-4484-ac72-8565b6ea4a5c">
</div>



## Creating Your Own Map for cub3D

To create a custom map for cub3D, follow these guidelines to ensure your map is properly formatted and compatible with the raycasting engine:

### Map Composition

Your map must be composed of only six possible characters:

- `0` for an empty space.
- `1` for a wall.
- `N`, `S`, `E`, or `W` for the player’s start position and spawning orientation.

### Map Structure Rules

1. **Enclosed Map:**
   - The map must be closed/surrounded by walls. If not, the program will return an error.

2. **Element Separation:**
   - Except for the map content, each type of element can be separated by one or more empty lines.

3. **Order of Elements:**
   - Except for the map content, each type of element can be set in any order in the file.

4. **Space Separation:**
   - Except for the map, each type of information from an element can be separated by one or more spaces.

### Example Map:

Here is an example of a simple valid map:

```plaintext
111111
100001
100N01
100001
111111
```

### Adding Walls Textures:
- North Texture:
  ```NO ./path_to_the_north_texture.xpm```

- South Texture:
  ```SO ./path_to_the_south_texture.xpm```

- West Texture:
  ```WE ./path_to_the_west_texture.xpm```

- East Texture:
  ```EA ./path_to_the_east_texture.xpm```

Replace ```path_to_the_x_texture``` with the name of your texture file.

### Example:
``` file.cub
NO ./north_texture.xpm
```

### Adding Floor and Ceiling Colors:
- Floor color:
  ```F  r, g, b```

- Ceiling color:
  ```C  r, g, b```

R,G,B colors in range [0,255]:

### Example:
``` file.cub
F  0, 255, 255
```


### How to Integrate Your Map
1. **Create a Text File:**
  - Open a text editor and create a new file for your map. Save it with a .cub extension.

2. **Define Map Elements:**
  - Use the characters `0`, `1` to define the map layout and `N`, `S`, `E`, `W`  for the player's starting position.

3. **Enclose the Map:**
  - Ensure that the map is enclosed by walls on all sides.

4. **Save and Run:**
  - Save the file in **maps/** and run the cub3D program with your map file as follows:

```shell
./cub3D maps/your_map_file.cub
```
Replace ```your_map_file``` with the name of your map file.

**Example Command:**
```shell
./cub3D maps/prova.cub
```
Now you're ready to explore your custom map using the cub3D raycasting engine!
