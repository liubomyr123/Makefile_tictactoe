#include <gtk/gtk.h>
#include <string.h>

#define PLAYER_1 "X"
#define PLAYER_2 "O"

_Bool IS_FIRST_PLAYER = 0;
const int POSITIONS_LENGTH = 9;
int WINDOW_WIDTH = 250;
int WINDOW_HEIGHT = 240;

typedef struct
{
    GtkWidget **buttons;
    GtkWidget *result;
} RestartParams;

typedef struct
{
    int position;
    GtkWidget **buttons;
    GtkWidget *result;
} ButtonClickedParams;

int get_winner_number(GtkWidget *buttons[], char player_number[1]);
_Bool get_is_game_has_steps(GtkWidget *buttons[]);
void on_button_clicked(GtkButton *button, gpointer user_data);
void on_restart_clicked(GtkButton *restart_button, gpointer user_data);
void draw_buttons(GtkWidget *grid, GtkWidget *buttons[], GtkWidget *result);

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *grid;
    GtkWidget *header;
    GtkWidget *footer;
    GtkWidget *view_title;
    GtkWidget *view_sub_title;
    GtkWidget *result;
    GtkWidget *button_restart;

    GtkTextBuffer *buffer_title;
    GtkTextBuffer *buffer_sub_title;

    GtkWidget *buttons[POSITIONS_LENGTH];

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TicTacToe");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    fixed = gtk_fixed_new();
    grid = gtk_fixed_new();
    header = gtk_fixed_new();
    footer = gtk_fixed_new();

    result = gtk_label_new("Result:");
    view_sub_title = gtk_label_new("Player 1 (X) - Player 2 (O)");
    button_restart = gtk_button_new_with_label("Restart");

    draw_buttons(grid, buttons, result);

    GtkWidget *restart_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(restart_box), TRUE);
    gtk_box_pack_start(GTK_BOX(restart_box), button_restart, FALSE, FALSE, 0);
    gtk_widget_set_halign(restart_box, GTK_ALIGN_CENTER);

    gtk_label_set_justify(GTK_LABEL(result), GTK_JUSTIFY_FILL);
    gtk_label_set_justify(GTK_LABEL(view_sub_title), GTK_JUSTIFY_FILL);

    gtk_fixed_put(GTK_FIXED(header), restart_box, (WINDOW_WIDTH / 2) - 78, 0);

    RestartParams *params = g_malloc(sizeof(RestartParams));
    params->buttons = buttons;
    params->result = result;
    g_signal_connect(button_restart, "clicked", G_CALLBACK(on_restart_clicked), params);

    gtk_fixed_put(GTK_FIXED(header), view_sub_title, 10, 40);
    gtk_fixed_put(GTK_FIXED(footer), result, 10, 40);

    gtk_fixed_put(GTK_FIXED(fixed), header, 0, 10);
    gtk_fixed_put(GTK_FIXED(fixed), grid, 0, 70);
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, 165);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
    gtk_box_pack_start(GTK_BOX(box), fixed, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_set_hexpand(box, TRUE);
    gtk_widget_set_vexpand(box, TRUE);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

int get_winner_number(GtkWidget *buttons[], char player_number[1])
{
    int combinations[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 1; i <= POSITIONS_LENGTH; i++)
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(*(buttons + i - 1)));
        if (strncmp(label, player_number, 1) == 0)
        {
            // X X X
            // 4 5 6
            // 7 8 9
            if (i == 1 || i == 2 || i == 3)
            {
                if (++combinations[0] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\tX X X\n");
                    g_print("\t4 5 6\n");
                    g_print("\t7 8 9\n");
                    g_print("\n");
                    break;
                }
            }
            // X 2 3
            // X 5 6
            // X 8 9
            if (i == 1 || i == 4 || i == 7)
            {
                if (++combinations[1] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\tX 2 3\n");
                    g_print("\tX 5 6\n");
                    g_print("\tX 8 9\n");
                    g_print("\n");
                    break;
                }
            }
            // X 2 3
            // 4 X 6
            // 7 8 X
            if (i == 1 || i == 5 || i == 9)
            {
                if (++combinations[2] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\tX 2 3\n");
                    g_print("\t4 X 6\n");
                    g_print("\t7 8 X\n");
                    g_print("\n");
                    break;
                }
            }
            // 1 2 3
            // 4 5 6
            // X X X
            if (i == 7 || i == 8 || i == 9)
            {
                if (++combinations[3] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\t1 2 3\n");
                    g_print("\t4 5 6\n");
                    g_print("\tX X X\n");
                    g_print("\n");
                    break;
                }
            }
            // 1 2 3
            // X X X
            // 7 8 9
            if (i == 4 || i == 5 || i == 6)
            {
                if (++combinations[4] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\t1 2 3\n");
                    g_print("\tX X X\n");
                    g_print("\t7 8 9\n");
                    g_print("\n");
                    break;
                }
            }
            // 1 X 3
            // 4 X 6
            // 7 X 9
            if (i == 2 || i == 5 || i == 8)
            {
                if (++combinations[5] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\t1 X 3\n");
                    g_print("\t4 X 6\n");
                    g_print("\t7 X 9\n");
                    g_print("\n");
                    break;
                }
            }
            // 1 2 X
            // 4 5 X
            // 7 8 X
            if (i == 3 || i == 6 || i == 9)
            {
                if (++combinations[6] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\t1 2 X\n");
                    g_print("\t4 5 X\n");
                    g_print("\t7 8 X\n");
                    g_print("\n");
                    break;
                }
            }
            // 1 2 X
            // 4 X 6
            // X 8 9
            if (i == 3 || i == 5 || i == 7)
            {
                if (++combinations[7] == 3)
                {
                    g_print("Winner combination:\n");
                    g_print("\n");
                    g_print("\t1 2 X\n");
                    g_print("\t4 X 6\n");
                    g_print("\tX 8 9\n");
                    g_print("\n");
                    break;
                }
            }
        }
    }

    int winner_combination = -1;
    for (int i = 0; i < 8; i++)
    {
        if (combinations[i] == 3)
        {
            winner_combination = i;
        }
    }

    int winner_number = player_number == PLAYER_1 ? 1 : 2;
    return winner_combination != -1 ? winner_number : -1;
}

_Bool get_is_game_has_steps(GtkWidget *buttons[])
{
    _Bool is_game_has_steps = 0;
    for (GtkWidget **p_button = buttons; p_button < buttons + POSITIONS_LENGTH; p_button++)
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(*p_button));
        if (strncmp(label, PLAYER_1, 1) != 0 && strncmp(label, PLAYER_2, 1) != 0)
        {
            is_game_has_steps = 1;
        }
    }

    return is_game_has_steps;
}

void on_button_clicked(GtkButton *button, gpointer user_data)
{
    IS_FIRST_PLAYER = !IS_FIRST_PLAYER;
    char *label = IS_FIRST_PLAYER ? PLAYER_1 : PLAYER_2;
    gtk_button_set_label(button, label);
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);

    ButtonClickedParams *params = (ButtonClickedParams *)user_data;
    int winner_player_number = get_winner_number(params->buttons, label);
    if (winner_player_number == -1)
    {
        _Bool is_game_has_steps = get_is_game_has_steps(params->buttons);
        if (!is_game_has_steps)
        {
            g_print("Winning combination was not found\n");
            g_print("Game ends\n");
            gtk_label_set_text(GTK_LABEL(params->result), "Game over");
            return;
        }
        return;
    }

    g_print("Result: player %d won.\n", winner_player_number);

    char *winner_label = g_strdup_printf("Result: player %s won.", label);
    gtk_label_set_text(GTK_LABEL(params->result), winner_label);

    for (GtkWidget **p_button = params->buttons; p_button < params->buttons + POSITIONS_LENGTH; p_button++)
    {
        if (GTK_IS_BUTTON(*p_button))
        {
            gtk_widget_set_sensitive(GTK_WIDGET(*p_button), FALSE);
        }
    }
}

void on_restart_clicked(GtkButton *restart_button, gpointer user_data)
{
    RestartParams *params = (RestartParams *)user_data;
    gtk_label_set_text(GTK_LABEL(params->result), "Result:");

    IS_FIRST_PLAYER = 0;
    for (GtkWidget **p_button = params->buttons; p_button < params->buttons + POSITIONS_LENGTH; p_button++)
    {
        if (GTK_IS_BUTTON(*p_button))
        {
            gtk_widget_set_sensitive(GTK_WIDGET(*p_button), TRUE);
            gtk_button_set_label(GTK_BUTTON(*p_button), "_");
        }
    }
}

void draw_buttons(GtkWidget *grid, GtkWidget *buttons[], GtkWidget *result)
{
    int x_coordinate = 0;
    int y_coordinate = 0;
    for (int p_button_number = 1; p_button_number <= POSITIONS_LENGTH; p_button_number++)
    {
        int padding = 5;
        int button_width = 50 + padding;
        int button_height = 34 + padding;
        buttons[p_button_number - 1] = gtk_button_new_with_label("_");

        ButtonClickedParams *params = g_malloc(sizeof(ButtonClickedParams));
        params->position = p_button_number;
        params->buttons = buttons;
        params->result = result;

        g_signal_connect(buttons[p_button_number - 1], "clicked", G_CALLBACK(on_button_clicked), params);

        if (p_button_number == 4)
        {
            x_coordinate = 0;
            y_coordinate = 1;
        }

        if (p_button_number == 7)
        {
            x_coordinate = 0;
            y_coordinate = 2;
        }

        double new_x_coordinate = 10 + button_width * x_coordinate;
        double new_y_coordinate = 10 + button_height * y_coordinate;
        gtk_fixed_put(GTK_FIXED(grid), buttons[p_button_number - 1], new_x_coordinate, new_y_coordinate);
        x_coordinate++;
    }
}
