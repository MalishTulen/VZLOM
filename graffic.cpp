#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "TXlib.h"
#include "graffic.h"

//int speed_vector = [0, 0];

int graffic ()
{
    txCreateWindow ( SCREEN_LENGTH, SCREEN_HIGHT );

    txSetFillColor ( TX_BLACK );
    txSetColor ( TX_WHITE, 3 );

    start_simulation ();

    return 0;
}

void make_box_with_message ( double x0, double y0, double x1, double y1, const char* message )
{
    txRectangle ( ( x0 ), ( y0 ), ( x1 ), ( y1 ) );
    txDrawText ( x0, y0, x1, y1, message );
}

int start_simulation ()
{
    srand(( unsigned int )time(0));

    player_t player1 = {};
    player_t player2 = {};
    sword_t sword = {};
    ctor ( &player1, &player2, &sword );

    static int hp_sum = 0;
    bool pencil = true;
    while ( pencil )
    {
        hp_sum = player1.hp + player2.hp;

        if ( !sword.is_sword_active )
            spawn_sword ( &player1, &player2, &sword );         //if sword.is_sword_active == false: spawn_sword
        else                                                    //else: check collisions of sword with players
        {
            if ( !player1.is_armored && !player2.is_armored )
            {
                check_sword_collision ( &player1, &sword );
                check_sword_collision ( &player2, &sword );
            }
        }

        remove_previos_frame ( &player1 );
        remove_previos_frame ( &player2 );

        print_player_frame ( &player1, &player2, &sword, TX_RED );
        print_player_frame ( &player2, &player1, &sword, TX_YELLOW );

        hp_sum = hp_sum - player1.hp - player2.hp;

        display_hp ( &player1, &player2, hp_sum );


        check_if_player_died ( &player1, &player2, &pencil );
        check_if_player_died ( &player2, &player1, &pencil );

        check_for_exit ( &pencil );

        Sleep(1);
    }

    dtor ( &player1, &player2, &sword );

    return 0;
}

int ctor ( player_t* player1, player_t* player2, sword_t* sword )
{
    assert ( player1 && "bad player1 in ctor");
    assert ( player1 && "bad player2 in ctor");
    assert ( player1 && "sword in ctor");

    double x0 = (SCREEN_LENGTH - max_string_length)/2;
    double y0 = 100;

    print_menu ( x0, y0 );

    sword->is_sword_active = false;

    player1->vector = ( int* ) calloc ( 2, sizeof ( int ) );
    player2->vector = ( int* ) calloc ( 2, sizeof ( int ) );
    player1->left_corner_pos = ( int* ) calloc ( 2, sizeof ( int ) );
    player2->left_corner_pos = ( int* ) calloc ( 2, sizeof ( int ) );

    for ( int i = 0; i < 2; i++ )
    {
        player1->vector[i] = velocity;
        player2->vector[i] = -velocity;

        player1->left_corner_pos[i] = 0;
        player2->left_corner_pos[i] = 0;
    }

    player1->hp = start_hp_amount;
    player2->hp = start_hp_amount;

    player1->is_armored = false;
    player2->is_armored = false;

    player1->is_sound_playing = false;
    player2->is_sound_playing = false;

    fighters_chooser ( x0, y0, &player1->color_number, &player2->color_number );
    set_fighters_name ( player1 );
    set_fighters_name ( player2 );
    txSetColor ( TX_BLACK );
    txClear();
    set_start_positions ( player1->left_corner_pos, player2->left_corner_pos );

    return 0;
}

void print_menu ( double x0, double y0 )
{
    make_box_with_message ( x0, 30, x0 + max_string_length, 70, intro_string );

    for ( int i = 0; i < 4; i++ )
    {
        //printf ( "FIGHTER %d\n", i+1 );
        double y = y0 + ( double )i*60;
        make_box_with_message ( x0, y, x0 + max_string_length, y+40, (fighters[i] ) );
        //printf ( "NIGGER %d\n", i+1 );
    }

    txDrawText ( 40, 380, 360, 450, "LMB - first fighter\n RMB - second fighter");
}

int fighters_chooser ( double x0, double y0, int* player1_num, int* player2_num )
{
    bool picun = true;
    while ( picun )
    {
        //CHECK_IF_MOUSE_BUTTON1_PRESSED
        if ( txMouseButtons() == LEFT_MOUSE_BUTTON )
        {
            check_if_both_players_choosed_and_the_GO_pressed ( player1_num, player2_num, &picun );

            check_if_any_fighter_was_choosed ( player1_num, x0, y0,  TX_RED );
            txSleep();
        }

        if ( txMouseButtons() == RIGHT_MOUSE_BUTTON )
        {
            check_if_any_fighter_was_choosed ( player2_num, x0, y0, TX_YELLOW );

            txSleep();
        }

        print_go_if_both_players_choosed ( player1_num, player2_num, &picun );
    }

    return 0;
}

int set_fighters_name ( player_t* player )
{
    if ( player->color_number == TRALALEILO_TRALALA )
    {
        sprintf ( player->name, "TRALALEILO TRALALA" );
        player->image_link = txLoadImage( "image1.bmp" );
        if (!player->image_link)
        {
            printf("Ошибка загрузки изображения!");
            return 1;
        }
        player->sound_name = song_names[0];
    }
    else if ( player->color_number == BOMBARDIRO_CROCODILO )
    {
        sprintf ( player->name, "BOMBARDIRO CROCODILO" );
        player->image_link = txLoadImage( "image2.bmp" );
        if (!player->image_link)
        {
            printf("Ошибка загрузки изображения!");
            return 1;
        }
        player->sound_name = song_names[1];
    }
    else if ( player->color_number == BRR_BRR_PATAPIM )
    {
        sprintf ( player->name, "BRR BRR PATAPIM" );
        player->image_link = txLoadImage( "image3.bmp" );
        if (!player->image_link)
        {
            printf("Ошибка загрузки изображения!");
            return 1;
        }
        player->sound_name = song_names[2];
    }
    else if ( player->color_number == TUNG_TUNG_SAGUR )
    {
        sprintf ( player->name, "TUNG TUNG SAGUR" );
        player->image_link = txLoadImage( "image4.bmp" );
        if (!player->image_link)
        {
            printf("Ошибка загрузки изображения!");
            return 1;
        }
        player->sound_name = song_names[3];
    }

    return 0;
}

int set_start_positions ( int* left_corner_1_pos, int* left_corner_2_pos )
{
    for ( int i = 0; i < 2; i++ )
    {
        int coord1 = rand()%100;
        left_corner_1_pos[i] = coord1;

        int coord2 = rand()%(2*diametr);
        left_corner_2_pos[i] = SCREEN_LENGTH - 3*diametr + coord2 - i*200;

    }

    return 0;
}

int check_for_collisions ( player_t* player1, player_t* player2, sword_t* sword )
{
    check_player_collision_with_walls ( player1 );

    //collision with other cube

    check_player_collision_with_player ( player1, player2, sword );

    return 0;
}


int spawn_sword ( player_t* player1, player_t* player2, sword_t* sword )
{
    sword->left_corner_pos[0] = 125 + rand()%500;
    sword->left_corner_pos[1] = 125 + rand()%300;

    //check for collisions

    sword->is_sword_pos_ok = false;
    sword->is_sword_active = true;

    set_available_sword_coords ( player1, player2, sword );

    print_sword ( sword );

    return 0;
}

int check_sword_collision ( player_t* player, sword_t* sword )
{
    if ( sword->left_corner_pos[0] + sword_diametr >= player->left_corner_pos[0]
       && sword->left_corner_pos[0] <= player->left_corner_pos[0] + diametr
       && sword->left_corner_pos[1] + sword_diametr >= player->left_corner_pos[1]
       && sword->left_corner_pos[1] <= player->left_corner_pos[1] + diametr )
    {
        player->is_armored = true;
        txSetFillColor ( TX_BLACK );
        txSetColor ( TX_BLACK );
        txRectangle ( sword->left_corner_pos[0], sword->left_corner_pos[1], sword->left_corner_pos[0] + sword_diametr, sword->left_corner_pos[1] + sword_diametr );
    }

    return 0;
}


int display_hp ( player_t* player1, player_t* player2, int hp_change )
{
    if ( hp_change != 0 )
    {
        txSetFillColor ( TX_BLACK );
        txSetColor ( TX_BLACK );
        txClear();
    }
    //txSelectFont ( "Arial", 20, 0, FW_BOLD );
    txSetColor ( TX_RED );
    char buffer1[MAX_BUF_SIZE] = {};
    sprintf ( buffer1, "%s - %d HP\n", player1->name, player1->hp );
    txTextOut ( 50, 50, buffer1 );

    txSetColor ( TX_YELLOW );
    char buffer2[MAX_BUF_SIZE] = {};
    sprintf ( buffer2, "%s - %d HP\n", player2->name, player2->hp );
    txTextOut ( 50, 100, buffer2 );

    return 0;
}


int check_if_both_players_choosed_and_the_GO_pressed ( int* player1_num, int* player2_num, bool* picun )
{
    if ( (*player1_num) * *(player2_num) != 0 )
    {
        RECT area = { SCREEN_LENGTH/2 - 20, 500, SCREEN_LENGTH/2 + 20, 540 };

        if ( my_in ( txMousePos (), area ) )
            *picun = false;

    }

    return 0;
}

int check_if_any_fighter_was_choosed ( int* player_num, double x0, double y0, COLORREF color )
{
    for ( int i = 0; i < 4; i++ )
    {
        long y = (long)y0 + (long)i * 60;

        RECT area = { (long)x0, y, (long)x0 + max_string_length, y + 40 };

        if ( my_in ( txMousePos (), area ) )
        {
            //printf ( "ZALUPA%d\n", i + 1 );
            if ( (*player_num) != 0 )
                make_box_with_message ( x0, y0 + (double)((*player_num) - 1) * 60 , x0 + max_string_length,
                                        (y0 + (double)((*player_num)-1) * 60)+40, (fighters[(*player_num)-1] ) );

            txSetColor ( color );
            make_box_with_message ( x0, y, x0 + max_string_length, y+40, (fighters[i] ) );
            txSetColor ( TX_WHITE );
            (*player_num) = i + 1;
        }

    }
    return 0;
}

int print_go_if_both_players_choosed ( int* player1_num, int* player2_num, bool* picun )
{
    if ( (*player1_num) * (*player2_num) != 0 )
    {
        make_box_with_message ( SCREEN_LENGTH/2 - 20, 500, SCREEN_LENGTH/2 + 20, 540, "GO" );

        if ( txGetAsyncKeyState ( VK_RETURN ) )
            *picun = false;
    }

    return 0;
}



int remove_previos_frame ( player_t* player )
{
    txSetColor ( TX_BLACK, 3 );
    txSetFillColor ( TX_TRANSPARENT );
    //printf ( "picun4\n" );
    txRectangle( player->left_corner_pos[0] - 3, player->left_corner_pos[1] - 3, player->left_corner_pos[0]+diametr + 3, player->left_corner_pos[1] + diametr + 3 );
    //printf ( "picun5\n" );
    return 0;
}

int change_left_corner_pos ( player_t* player )
{
    for ( int i = 0; i < 2; i++ )
            player->left_corner_pos[i] += player->vector[i];

    return 0;
}

int print_player_frame ( player_t* player1, player_t* player2, sword_t* sword, COLORREF color )
{
    change_left_corner_pos ( player1 );

    /*txSetFillColor ( color );
    txSetColor ( color );
    txRectangle( player1->left_corner_pos[0], player1->left_corner_pos[1], player1->left_corner_pos[0] + diametr, player1->left_corner_pos[1] + diametr );*/
    if ( player1->is_armored == true )
    {
        if ( !player1->is_sound_playing )
        {
            txPlaySound ( player1->sound_name, SND_LOOP );
            player1->is_sound_playing = true;
        }
        txSetColor ( TX_GREEN, 3 );
        txSetFillColor ( TX_TRANSPARENT );
        txRectangle ( player1->left_corner_pos[0] - 2, player1->left_corner_pos[1] - 2, player1->left_corner_pos[0] + diametr + 2, player1->left_corner_pos[1] + diametr + 2 );
    }
    txBitBlt ( double ( player1->left_corner_pos[0] + 1 ), double ( player1->left_corner_pos[1] + 1 ), player1->image_link );
    //printf ( "picun5\n" );
    check_for_collisions ( player1, player2, sword );

    return 0;
}

int check_if_player_died ( player_t* player1, player_t* player2, bool* pencil )
{
    if ( player1->hp == 0 )
    {
        txSetColor ( TX_WHITE );
        char buffer[MAX_BUF_SIZE] = {};
        sprintf ( buffer, "%s WINS!\n", player2->name );
        txTextOut ( 250, 300, buffer );
        *pencil = false;
    }

    return 0;
}

int check_player_collision_with_walls ( player_t* player )
{
    if ( player->left_corner_pos[0] == 0 || player->left_corner_pos[0] == SCREEN_LENGTH - diametr - 1 )
    {
        player->vector[0] *= -1;
        //txPlaySound ( song_names[4] );
    }

    if ( player->left_corner_pos[1] == 0 || player->left_corner_pos[1] == SCREEN_HIGHT - diametr - 1 )
    {
        player->vector[1] *= -1;
        //txPlaySound ( song_names[4] );
    }

    return 0;
}

int check_player_collision_with_player ( player_t* player1, player_t* player2, sword_t* sword )
{
    check_opposite_sides_collision ( RIGHT_AND_LEFT, player1, player2, sword );
    check_opposite_sides_collision ( TOP_AND_BOTTOM, player1, player2, sword );

    return 0;
}

int check_opposite_sides_collision ( int opposite_sides, player_t* player1, player_t* player2, sword_t* sword )
{
    int other_opposite_sides = -opposite_sides + 1 ;
    if ( player1->left_corner_pos[ opposite_sides ] + diametr == player2->left_corner_pos[ opposite_sides ]
        || player1->left_corner_pos[ opposite_sides ] == player2->left_corner_pos[ opposite_sides ] + diametr )
    {
        if ( player2->left_corner_pos[ other_opposite_sides ] >= player1->left_corner_pos[ other_opposite_sides ] - diametr
             && player2->left_corner_pos[ other_opposite_sides ] <= player1->left_corner_pos[ other_opposite_sides ] + diametr )
        {
            player1->vector[ opposite_sides ] *= -1;
            player2->vector[ opposite_sides ] *= -1;
            if ( player1->is_armored == true )
            {
                player2->hp --;
                player1->is_armored = false;
                sword->is_sword_active = false;
                player1->is_sound_playing = false;
                txPlaySound ( NULL );
                //printf ( "PLAYER 2 LOST 1 HP\n" );
            }

            else if ( player2->is_armored == true )
            {
                player1->hp --;
                player2->is_armored = false;
                sword->is_sword_active = false;
                player2->is_sound_playing = false;
                txPlaySound ( NULL );
                //printf ( "PLAYER 1 LOST 1 HP\n" );
            }

        }

    }

    return 0;
}

int set_available_sword_coords ( player_t* player1, player_t* player2, sword_t* sword )
{
    static int iteration_counter = 0;

    while ( (sword->is_sword_pos_ok) )
    {
        iteration_counter++;
        check_sword_collision ( player1, sword );
        check_sword_collision ( player2, sword );


        if ( !(sword->is_sword_pos_ok) )
        {
            if ( iteration_counter % 4 == 0 )
            {
                sword->left_corner_pos[0] += sword_diametr;
                sword->left_corner_pos[1] += sword_diametr;
            }
            else if ( iteration_counter % 4 == 1 || iteration_counter % 4 == 3 )
                sword->left_corner_pos[0] += 2*( SCREEN_LENGTH/2 - sword->left_corner_pos[0] );
            else if ( iteration_counter % 4 == 2 )
                sword->left_corner_pos[1] += 2*( SCREEN_HIGHT/2 - sword->left_corner_pos[1] );
        }
        else
            sword->is_sword_pos_ok = true;
    }

    return 0;
}

int print_sword ( sword_t* sword )
{
    txSetColor ( TX_GREEN );
    txSetFillColor ( TX_GREEN );
    txRectangle ( sword->left_corner_pos[0], sword->left_corner_pos[1], sword->left_corner_pos[0] + sword_diametr, sword->left_corner_pos[1] + sword_diametr );

    sword->is_sword_active = true;
    sword->is_sword_pos_ok = true;

    return 0;
}

int dtor ( player_t* player1, player_t* player2, sword_t* sword )
{
    free ( player1->left_corner_pos );
    free ( player1->vector );
    free ( player2->left_corner_pos );
    free ( player2->vector );

    txDeleteDC ( player1->image_link );
    txDeleteDC ( player2->image_link );

    return 0;
}

bool my_in ( POINT mouse_pos, RECT area )
{
    if ( mouse_pos.x >= area.left &&
         mouse_pos.x <= area.right &&
         mouse_pos.y >= area.top &&
         mouse_pos.y <= area.bottom )
         return true;

    return false;
}

void check_for_exit ( bool* pencil )
{
    if ( txGetAsyncKeyState( VK_SHIFT ) )
        *pencil = false;
}
