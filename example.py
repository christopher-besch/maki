import maki
from PIL import Image
import numpy as np
import itertools
import os

maki.init(maki.RendererImplementation.opengl)
render_driver = maki.RenderDriver("Maki Showcase Window", 1280, 720)

# again, garbage code
class ImageRects:
    rects = []
    WIDTH = 96
    HEIGHT = 72
    SPACING = 3
    
    def __init__(self, render_driver: maki.RenderDriver, first_frame: int, after_last_frame: int, path: str, z: float):
        self.render_driver = render_driver
        
        image = Image.open(path)
        image = image.resize((self.WIDTH, self.HEIGHT), Image.ANTIALIAS)
        image_data = np.asarray(image)
        
        for (x, y), frame in zip(itertools.product(range(self.WIDTH), range(self.HEIGHT)), np.linspace(first_frame, after_last_frame, num=self.WIDTH*self.HEIGHT, endpoint=False)):
            # create rect
            self.rects.append(self.render_driver.add_quadrilateral_atom())
            print("created")
            # position rect
            self.render_driver.translate_quadrilateral_atom(self.rects[-1], 1, maki.vec3(x * self.SPACING, -y * self.SPACING, z))
            print("translated")
            # set color
            self.render_driver.color_quadrilateral_atom(self.rects[-1], 1, maki.vec4(float(image_data[y][x][0]/256), float(image_data[y][x][1]/256), float(image_data[y][x][2]/256), 1.0))
            print("coloured")
            # show rect
            self.render_driver.show_quadrilateral_atom(self.rects[-1], int(frame), True)
            print("showed")
            
        print(f"created {path}")
        
    def show(self, frame: int):
        for cube in self.cubes:
            self.render_driver.show_quadrilateral_atom(cube, frame, True)
    def hide(self, frame: int):
        for rect in self.rects:
            self.render_driver.show_quadrilateral_atom(rect, frame, True)
        
    def translate(self, delta: maki.vec3, first_frame: int, after_last_frame: int):
        alpha_delta = 1 / (after_last_frame - first_frame)
        for frame in range(first_frame, after_last_frame):
            cur_delta = delta * alpha_delta
            for rect in self.rects:
                self.render_driver.translate_quadrilateral_atom(rect, frame, cur_delta)

class VideoRects:
    images = []
    SPACING = 3
    
    def __init__(self, render_driver: maki.RenderDriver, first_frame: int, after_last_frame: int, path: str, frames):
        self.render_driver = render_driver
        
        frame_space = np.linspace(first_frame, after_last_frame, num=frames+1, endpoint=False)
        
        for frame in range(1, frames+1):
            self.images.append(ImageRects(self.render_driver, frame_space[frame-1], frame_space[frame], os.path.join(path, f"{frame:02d}.png"), frame * self.SPACING))
    
    def show(self, frame: int):
        for image in self.images:
            image.show(frame)
    def hide(self, frame: int):
        for image in self.images:
            image.hide(frame)
    def translate(self, delta: maki.vec3, first_frame: int, after_last_frame: int):
        for image in self.images:
            image.translate(delta, first_frame, after_last_frame)
    
t = VideoRects(render_driver, 500, 1000, "examples/rick", 31)
