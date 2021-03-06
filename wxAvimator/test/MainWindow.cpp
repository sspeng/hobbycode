// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "MainWindow.h"

Fl_Menu_Item MainWindow::menu_[] = {
 {"File", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"New", 0x4006e,  (Fl_Callback*)cb_New, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {"Open File...", 0x4006f,  (Fl_Callback*)cb_Open, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {"Save", 0x40073,  (Fl_Callback*)cb_Save, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {"Save As...", 0,  (Fl_Callback*)cb_SaveAs, 0, 128, FL_NORMAL_LABEL, 0, 12, 0},
 {"Exit", 0,  (Fl_Callback*)cb_Exit, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Edit", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"Copy Frame", 0x40063,  (Fl_Callback*)cb_CopyFrame, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {"Paste Frame", 0x40076,  (Fl_Callback*)cb_PasteFrame, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Options", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"Figure", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"Male", 0,  (Fl_Callback*)cb_FigureMale, 0, 12, FL_NORMAL_LABEL, 0, 12, 0},
 {"Female", 0,  (Fl_Callback*)cb_FigureFemale, 0, 8, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Skeleton", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"Show", 0,  (Fl_Callback*)cb_JointsShow, 0, 8, FL_NORMAL_LABEL, 0, 12, 0},
 {"Hide", 0,  (Fl_Callback*)cb_JointsHide, 0, 12, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Joint Limits", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 12, 0},
 {"On", 0,  (Fl_Callback*)cb_LimitsOn, 0, 8, FL_NORMAL_LABEL, 0, 12, 0},
 {"Off", 0,  (Fl_Callback*)cb_LimitsOff, 0, 12, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Loop", 0,  (Fl_Callback*)cb_Loop, 0, 6, FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};
Fl_Menu_Item* MainWindow::editPasteFrame = MainWindow::menu_ + 9;
Fl_Menu_Item* MainWindow::limits = MainWindow::menu_ + 21;

Fl_Menu_Item MainWindow::menu_partChoice[] = {
 {"hip", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"abdomen", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"chest", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"neck", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"head", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lCollar", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lShldr", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lForeArm", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lHand", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rCollar", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rShldr", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rForeArm", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rHand", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lThigh", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lShin", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"lFoot", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rThigh", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rShin", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {"rFoot", 0,  0, 0, 4, FL_NORMAL_LABEL, 0, 10, 7},
 {0,0,0,0,0,0,0,0,0}
};
MainWindow::MainWindow(int X, int Y, int W, int H, const char *L)
  : Fl_Double_Window(X, Y, W, H, L) {
  _MainWindow();
}

MainWindow::MainWindow(int W, int H, const char *L)
  : Fl_Double_Window(0, 0, W, H, L) {
  clear_flag(16);
  _MainWindow();
}

void MainWindow::_MainWindow() {
  MainWindow *w = this;
  MainWindow *o = this;
o->box(FL_FLAT_BOX);
o->color(FL_FOREGROUND_COLOR);
o->selection_color(FL_BACKGROUND_COLOR);
o->labeltype(FL_NO_LABEL);
o->labelfont(0);
o->labelsize(14);
o->labelcolor(FL_FOREGROUND_COLOR);
o->callback((Fl_Callback*)cb_MainWindow);
o->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
o->when(FL_WHEN_RELEASE);
{ Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 800, 25);
  o->box(FL_PLASTIC_UP_BOX);
  o->down_box(FL_PLASTIC_DOWN_BOX);
  o->color(FL_BACKGROUND2_COLOR);
  o->labelsize(12);
  o->labelcolor(FL_DARK3);
  o->textsize(12);
  o->menu(menu_);
}
{ Fl_Pack* o = new Fl_Pack(0, 25, 800, 575);
  { Fl_Pack* o = new Fl_Pack(0, 25, 800, 550);
    o->type(1);
    o->color(FL_BACKGROUND2_COLOR);
    { AnimationView* o = view = new AnimationView(0, 25, 640, 550);
      o->box(FL_FLAT_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->selection_color(FL_BACKGROUND_COLOR);
      o->labeltype(FL_NORMAL_LABEL);
      o->labelfont(0);
      o->labelsize(14);
      o->labelcolor(FL_FOREGROUND_COLOR);
      o->callback((Fl_Callback*)cb_AnimationView);
      o->align(FL_ALIGN_CENTER);
      o->when(FL_WHEN_RELEASE);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(640, 25, 160, 550);
      o->color(FL_FOREGROUND_COLOR);
      o->selection_color((Fl_Color)55);
      { Fl_Choice* o = partChoice = new Fl_Choice(700, 35, 90, 20, "Edit Part: ");
        o->tooltip("Select body part to edit");
        o->box(FL_DOWN_BOX);
        o->down_box(FL_BORDER_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_PartChoice);
        o->menu(menu_partChoice);
        o->value(1);
      }
      { Fl_Roller* o = xRotRoller = new Fl_Roller(650, 80, 140, 20);
        o->type(1);
        o->minimum(-180);
        o->maximum(180);
        o->step(1);
        o->callback((Fl_Callback*)cb_RotRoller);
      }
      { Fl_Value_Input* o = xRotValue = new Fl_Value_Input(710, 65, 45, 15, "X-Rotation: ");
        o->tooltip("Current X-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-180);
        o->maximum(180);
        o->step(0.01);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_RotValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Roller* o = yRotRoller = new Fl_Roller(650, 120, 140, 20);
        o->type(1);
        o->minimum(-180);
        o->maximum(180);
        o->step(1);
        o->callback((Fl_Callback*)cb_RotRoller);
      }
      { Fl_Value_Input* o = yRotValue = new Fl_Value_Input(710, 105, 45, 15, "Y-Rotation: ");
        o->tooltip("Current Y-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-180);
        o->maximum(180);
        o->step(0.01);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_RotValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Roller* o = zRotRoller = new Fl_Roller(650, 160, 140, 20);
        o->type(1);
        o->minimum(-180);
        o->maximum(180);
        o->step(1);
        o->callback((Fl_Callback*)cb_RotRoller);
      }
      { Fl_Value_Input* o = zRotValue = new Fl_Value_Input(710, 145, 45, 15, "Z-Rotation: ");
        o->tooltip("Current Z-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-180);
        o->maximum(180);
        o->step(0.01);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_RotValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Roller* o = xPosRoller = new Fl_Roller(650, 230, 140, 20);
        o->type(1);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(1);
        o->callback((Fl_Callback*)cb_PosRoller);
      }
      { Fl_Value_Input* o = xPosValue = new Fl_Value_Input(710, 215, 45, 15, "X-Position: ");
        o->tooltip("Current X-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(0.01);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_PosValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Roller* o = yPosRoller = new Fl_Roller(650, 270, 140, 20);
        o->type(1);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(1);
        o->value(43);
        o->callback((Fl_Callback*)cb_PosRoller);
      }
      { Fl_Value_Input* o = yPosValue = new Fl_Value_Input(710, 255, 45, 15, "Y-Position: ");
        o->tooltip("Current Y-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(0.01);
        o->value(43);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_PosValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Roller* o = zPosRoller = new Fl_Roller(650, 310, 140, 20);
        o->type(1);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(1);
        o->callback((Fl_Callback*)cb_PosRoller);
      }
      { Fl_Value_Input* o = zPosValue = new Fl_Value_Input(710, 295, 45, 15, "Z-Position: ");
        o->tooltip("Current Z-Rotation in degrees");
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color((Fl_Color)31);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(-196.85);
        o->maximum(196.85);
        o->step(0.01);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_PosValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      { Fl_Output* o = new Fl_Output(765, 145, 30, 15);
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->labeltype(FL_NO_LABEL);
        o->labelsize(10);
        o->textsize(10);
        o->textcolor(4);
        o->align(40|FL_ALIGN_INSIDE);
        o->value("Ctrl");
      }
      { Fl_Output* o = new Fl_Output(765, 105, 30, 15);
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->labeltype(FL_NO_LABEL);
        o->labelsize(10);
        o->textsize(10);
        o->textcolor(2);
        o->align(40|FL_ALIGN_INSIDE);
        o->value("Alt");
      }
      { Fl_Output* o = new Fl_Output(765, 65, 30, 15);
        o->box(FL_FLAT_BOX);
        o->color(FL_FOREGROUND_COLOR);
        o->selection_color(FL_BACKGROUND2_COLOR);
        o->labeltype(FL_NO_LABEL);
        o->labelsize(10);
        o->textsize(10);
        o->textcolor(1);
        o->align(40|FL_ALIGN_INSIDE);
        o->value("Shift");
      }
      { Fl_Value_Input* o = fpsValue = new Fl_Value_Input(765, 555, 30, 15, "FPS: ");
        o->tooltip("Frames per second");
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)30);
        o->selection_color(FL_FOREGROUND_COLOR);
        o->labelsize(10);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->minimum(1);
        o->maximum(300);
        o->step(0.01);
        o->value(30);
        o->textsize(10);
        o->textcolor(7);
        o->callback((Fl_Callback*)cb_fpsValue);
        o->soft(false);
        o->cursor_color(FL_WHITE);
      }
      o->end();
    }
    o->end();
    Fl_Group::current()->resizable(o);
  }
  { Fl_Pack* o = new Fl_Pack(0, 575, 800, 25);
    o->type(1);
    { Fl_Slider* o = frameSlider = new Fl_Slider(0, 575, 645, 25);
      o->tooltip("Drag to change frames");
      o->type(5);
      o->box(FL_PLASTIC_UP_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->selection_color((Fl_Color)3);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(10);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->minimum(1);
      o->step(1);
      o->value(1);
      o->callback((Fl_Callback*)cb_FrameSlider);
      o->align(FL_ALIGN_CENTER);
    }
    { Fl_Button* o = playBtn = new Fl_Button(645, 575, 25, 25);
      o->tooltip("Play/Pause Animation");
      o->box(FL_PLASTIC_UP_BOX);
      o->down_box(FL_PLASTIC_DOWN_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->callback((Fl_Callback*)cb_PlayBtn);
    }
    { Fl_Button* o = keyBtn = new Fl_Button(670, 575, 25, 25);
      o->tooltip("Toggle Keyframe");
      o->box(FL_PLASTIC_UP_BOX);
      o->down_box(FL_PLASTIC_DOWN_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->callback((Fl_Callback*)cb_KeyBtn);
    }
    { Fl_Group* o = new Fl_Group(695, 575, 105, 25);
    { Fl_Output* o = new Fl_Output(695, 575, 35, 25);
      o->box(FL_FLAT_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->labeltype(FL_NO_LABEL);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->textsize(10);
      o->textcolor(7);
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      o->value("Frame:");
    }
    { Fl_Value_Input* o = frameValue = new Fl_Value_Input(730, 580, 25, 15);
      o->tooltip("Current frame number");
      o->box(FL_FLAT_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(10);
      o->minimum(1);
      o->value(1);
      o->textsize(10);
      o->textcolor(7);
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    }
      { Fl_Output* o = new Fl_Output(745, 575, 15, 25);
      o->box(FL_FLAT_BOX);
      o->color(FL_FOREGROUND_COLOR);
      o->labeltype(FL_NO_LABEL);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->textsize(10);
      o->textcolor(7);
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      o->value("of ");
    }
      { Fl_Value_Input* o = numFramesValue = new Fl_Value_Input(765, 580, 30, 15);
      o->tooltip("Double-click to change animation length");
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)30);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(10);
      o->minimum(1);
      o->maximum(1800);
      o->step(1);
      o->value(1);
      o->textsize(10);
      o->textcolor(7);
      o->callback((Fl_Callback*)cb_NumFramesValue);
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      o->when(FL_WHEN_RELEASE);
      o->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);
        o->cursor_color(FL_WHITE);
      }
      o->end();
    }
    o->end();
  }
  o->end();
  Fl_Group::current()->resizable(o);
}
initialize();
end();
}
