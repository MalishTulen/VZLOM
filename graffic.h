#ifndef GRAFIC_HEADER
#define GRAFIC_HEADER

const int SCREEN_LENGTH     = 800;
const int SCREEN_HIGHT      = 600;
const int max_string_length = 320;
const int diametr           = 150;
const int sword_diametr     = 50;
const int start_hp_amount   = 3;
const int MAX_BUF_SIZE      = 500;

enum mouse_buttons
{
    LEFT_MOUSE_BUTTON = 1,
    RIGHT_MOUSE_BUTTON = 2,
};

enum fighters_numbers
{
    TRALALEILO_TRALALA = 1,
    BOMBARDIRO_CROCODILO = 2,
    BRR_BRR_PATAPIM = 3,
    TUNG_TUNG_SAGUR = 4,
};

enum opposite_sides
{
    RIGHT_AND_LEFT,
    TOP_AND_BOTTOM,
};
struct player_t
{
    int color_number;
    int* vector;
    int* left_corner_pos;
    int hp;
    bool is_armored;
    bool is_sound_playing;
    char name[30];
    HDC image_link;
    const char* sound_name;
};

struct sword_t
{
    bool is_sword_pos_ok;
    bool is_sword_active;
    int left_corner_pos[2];
};

int velocity = 1;//?:?:¹*:¹*?:¹*?:
const char song_names[5][30] = { "sound1.wav", "sound2.wav", "sound3.wav", "sound4.wav", "sound_ball.wav" };
const char fighters[4][30] = { "TRALALEILO TRALALA", "BOMBARDIRO CROCODOLO", "BRR BRR PATAPIM", "TUNG TUNG SAGUR" };
const char intro_string[20] = {"CHOOSE OPPONENTS"};

int graffic ();

void make_box_with_message ( double x0, double y0, double x1, double y1, const char* message );
int fighters_chooser ( double x1, double y0, int* player1_num, int* player2_num );
int start_simulation      ();
int set_start_positions   ( int* left_corner_1_pos, int* left_corner_2_pos );
int check_for_collisions  ( player_t* player1, player_t* player2, sword_t* sword );
int spawn_sword           ( player_t* player1, player_t* player2, sword_t* sword );
int check_sword_collision ( player_t* player, sword_t* sword );
int display_hp            ( player_t* player1, player_t* player2, int hp_change );
int set_fighters_name     ( player_t* player );
int check_if_both_players_choosed_and_the_GO_pressed ( int* player1_num, int* player2_num, bool* picun );
int check_if_any_fighter_was_choosed                 ( int* player_num, double x0, double y0, COLORREF color );
int print_go_if_both_players_choosed                 ( int* player1_num, int* player2_num, bool* picun );
void print_menu ( double x0, double y0 );
int ctor ( player_t* player1, player_t* player2, sword_t* sword );
int remove_previos_frame ( player_t* player );
int change_left_corner_pos ( player_t* player );
int print_player_frame ( player_t* player1, player_t* player2, sword_t* sword, COLORREF color );
int check_if_player_died ( player_t* player1, player_t* player2, bool* pencil );

int check_player_collision_with_player ( player_t* player1, player_t* player2, sword_t* sword );
int check_player_collision_with_walls ( player_t* player );
int check_opposite_sides_collision ( int opposite_walls, player_t* player1, player_t* player2, sword_t* sword );
int set_available_sword_coords ( player_t* player1, player_t* player2, sword_t* sword );
int print_sword ( sword_t* sword );
int dtor ( player_t* player1, player_t* player2, sword_t* sword );
bool my_in ( POINT mouse_pos, RECT area );
void check_for_exit ( bool* pencil );

#endif
