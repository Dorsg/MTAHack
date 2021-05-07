try:
    import Tkinter as tk
except:
    import tkinter as tk

import webbrowser

class TK():
    def __init__(self , accept ,cancel):
        self.root = tk.Tk()
        canvas1 = tk.Canvas(self.root, width=250, height=120)
        canvas1.pack()
        button_Play = tk.Button(self.root, text=accept, bg='green' , fg='white' , command=self.JoinZoomConversation)
        button_Quit = tk.Button(self.root, text=cancel, bg='brown' , fg='white', command=self.quit)
        canvas1.create_window(80 , 50 , window=button_Play)
        canvas1.create_window(200 , 50 , window=button_Quit)
        self.root.mainloop()

    def quit(self):
        self.root.destroy()

    def JoinZoomConversation(self):
        webbrowser.open('https://zoom.us/j/6275098211?pwd=YnE3NFpncVQ2WGRwckFoWXVTTzc0QT09')
        self.root.destroy()

