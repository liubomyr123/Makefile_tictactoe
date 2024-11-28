#include <gtk/gtk.h>
#include <string.h>

#define PLAYER_1 "X"
#define PLAYER_2 "O"

struct RestartParams
{
    GtkWidget **buttons;
    int positions_length;
    GtkWidget *result;
};

typedef struct
{
    int position;
    _Bool *is_first_player;
    int positions_length;
    GtkWidget **buttons;
    GtkWidget *result;
} ButtonClickedParams;

char get_winner_number(GtkWidget *buttons[], char player_number[1]);

_Bool get_is_game_has_steps(GtkWidget *buttons[], int positions_length)
{
    _Bool is_game_has_steps = 0;

    for (GtkWidget **p_button = buttons; p_button < buttons + positions_length; p_button++)
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(*p_button));

        if (
            strncmp(label, PLAYER_1, 1) != 0 &&
            strncmp(label, PLAYER_2, 1) != 0)
        {
            is_game_has_steps = 1;
        }
    }

    return is_game_has_steps;
}

void on_button_clicked(GtkButton *button, gpointer user_data)
{
    ButtonClickedParams *params = (ButtonClickedParams *)user_data;

    *params->is_first_player = !*params->is_first_player;
    gtk_button_set_label(button, *params->is_first_player ? PLAYER_1 : PLAYER_2);
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);

    _Bool is_game_has_steps = get_is_game_has_steps(params->buttons, params->positions_length);
    if (!is_game_has_steps)
    {
        g_print("Game ends\n");
        gtk_label_set_text(GTK_LABEL(params->result), "Game over");
        return;
    }

    char winner_number_1 = get_winner_number(params->buttons, PLAYER_1);
    char winner_number_2 = get_winner_number(params->buttons, PLAYER_2);

    if (winner_number_1 == '1')
    {
        g_print("Result: player %c won.\n", winner_number_1);

        char *winner_label = g_strdup_printf("Result: player %s won.", PLAYER_1);
        gtk_label_set_text(GTK_LABEL(params->result), winner_label);

        for (GtkWidget **p_button = params->buttons; p_button < params->buttons + params->positions_length; p_button++)
        {
            if (GTK_IS_BUTTON(*p_button))
            {
                gtk_widget_set_sensitive(GTK_WIDGET(*p_button), FALSE);
            }
            else
            {
                g_print("Not a button!\n");
            }
        }

        return;
    }
    if (winner_number_2 == '2')
    {
        g_print("Result: player %c won.\n", winner_number_2);

        char *winner_label = g_strdup_printf("Result: player %s won.", PLAYER_2);
        gtk_label_set_text(GTK_LABEL(params->result), winner_label);

        for (GtkWidget **p_button = params->buttons; p_button < params->buttons + params->positions_length; p_button++)
        {
            if (GTK_IS_BUTTON(*p_button))
            {
                gtk_widget_set_sensitive(GTK_WIDGET(*p_button), FALSE);
            }
            else
            {
                g_print("Not a button!\n");
            }
        }

        return;
    }
}

void on_restart_clicked(GtkButton *restart_button, gpointer user_data)
{
    struct RestartParams *params = (struct RestartParams *)user_data;

    gtk_label_set_text(GTK_LABEL(params->result), "Result:");

    for (GtkWidget **p_button = params->buttons; p_button < params->buttons + params->positions_length; p_button++)
    {
        if (GTK_IS_BUTTON(*p_button))
        {
            gtk_widget_set_sensitive(GTK_WIDGET(*p_button), TRUE);
            gtk_button_set_label(GTK_BUTTON(*p_button), "_");
        }
        else
        {
            g_print("Not a button!\n");
        }
    }
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    int positions[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int positions_length = sizeof(positions) / sizeof(int);
    _Bool is_first_player = 1;
    _Bool *p_is_first_player = &is_first_player;

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

    GtkWidget *buttons[positions_length];

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TicTacToe");
    int window_width = 250;
    int window_height = 240;
    gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    fixed = gtk_fixed_new();
    grid = gtk_fixed_new();
    header = gtk_fixed_new();
    footer = gtk_fixed_new();

    // view_title = gtk_label_new("\t      Tic Tac Toe");
    result = gtk_label_new("Result:");
    view_sub_title = gtk_label_new("Player 1 (X) - Player 2 (O)");
    button_restart = gtk_button_new_with_label("Restart");

    int padding = 5;
    int button_width = 50 + padding;
    int button_height = 34 + padding;
    int x = 0;
    int y = 0;

    for (int *p_button_number = positions; p_button_number < positions + positions_length; p_button_number++)
    {
        char *button_label = g_strdup_printf("%d", *p_button_number);
        buttons[*p_button_number - 1] = gtk_button_new_with_label("_");
        // buttons[*p_button_number - 1] = gtk_button_new_with_label(button_label);

        ButtonClickedParams *params = g_malloc(sizeof(ButtonClickedParams));
        params->is_first_player = p_is_first_player;
        params->position = *p_button_number;
        params->positions_length = positions_length;
        params->buttons = buttons;
        params->result = result;

        g_signal_connect(buttons[*p_button_number - 1], "clicked", G_CALLBACK(on_button_clicked), params);

        if (*p_button_number == 4)
        {
            x = 0;
            y = 1;
        }

        if (*p_button_number == 7)
        {
            x = 0;
            y = 2;
        }

        gtk_fixed_put(
            GTK_FIXED(grid),
            buttons[*p_button_number - 1],
            10 + button_width * x,
            10 + button_height * y);
        // g_print("Position: x: %d y: %d\n", 10 + button_width * x, 10 + button_height * y);
        x++;
    }

    GtkWidget *restart_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(restart_box), TRUE);
    gtk_box_pack_start(GTK_BOX(restart_box), button_restart, FALSE, FALSE, 0);
    gtk_widget_set_halign(restart_box, GTK_ALIGN_CENTER);

    gtk_label_set_justify(GTK_LABEL(result), GTK_JUSTIFY_FILL);
    gtk_label_set_justify(GTK_LABEL(view_sub_title), GTK_JUSTIFY_FILL);

    gtk_fixed_put(GTK_FIXED(header), restart_box, (window_width / 2) - 78, 0);

    struct RestartParams *params = g_malloc(sizeof(struct RestartParams));
    params->buttons = buttons;
    params->result = result;
    params->positions_length = positions_length;
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
    // gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

char get_winner_number(GtkWidget *buttons[], char player_number[1])
{
    char winner_number = '0';

    int combination_1[3] = {0, 0, 0};
    int combination_2[3] = {0, 0, 0};
    int combination_3[3] = {0, 0, 0};
    int combination_4[3] = {0, 0, 0};
    int combination_5[3] = {0, 0, 0};
    int combination_6[3] = {0, 0, 0};
    int combination_7[3] = {0, 0, 0};
    int combination_8[3] = {0, 0, 0};

    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    int count_5 = 0;
    int count_6 = 0;
    int count_7 = 0;
    int count_8 = 0;

    for (int i = 0; i < 9; i++)
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(*(buttons + i)));
        if (strncmp(label, player_number, 1) == 0)
        {
            // X X X
            // 4 5 6
            // 7 8 9
            if (i == 0 || i == 1 || i == 2)
            {
                combination_1[count_1] = 1;
                count_1++;

                if (combination_1[0] == 1 && combination_1[1] == 1 && combination_1[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // X 2 3
            // X 5 6
            // X 8 9
            if (i == 0 || i == 3 || i == 6)
            {
                combination_2[count_2] = 1;
                count_2++;

                if (combination_2[0] == 1 && combination_2[1] == 1 && combination_2[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // X 2 3
            // 4 X 6
            // 7 8 X
            if (i == 0 || i == 4 || i == 8)
            {
                combination_3[count_3] = 1;
                count_3++;

                if (combination_3[0] == 1 && combination_3[1] == 1 && combination_3[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // 1 2 3
            // 4 5 6
            // X X X
            if (i == 6 || i == 7 || i == 8)
            {
                combination_4[count_4] = 1;
                count_4++;

                if (combination_4[0] == 1 && combination_4[1] == 1 && combination_4[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // 1 2 3
            // X X X
            // 7 8 9
            if (i == 3 || i == 4 || i == 5)
            {
                combination_5[count_5] = 1;
                count_5++;

                if (combination_5[0] == 1 && combination_5[1] == 1 && combination_5[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // 1 X 3
            // 4 X 6
            // 7 X 9
            if (i == 1 || i == 4 || i == 7)
            {
                combination_6[count_6] = 1;
                count_6++;

                if (combination_6[0] == 1 && combination_6[1] == 1 && combination_6[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // 1 2 X
            // 4 5 X
            // 7 8 X
            if (i == 2 || i == 5 || i == 8)
            {
                combination_7[count_7] = 1;
                count_7++;

                if (combination_7[0] == 1 && combination_7[1] == 1 && combination_7[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
            // 1 2 X
            // 4 X 6
            // X 8 9
            if (i == 2 || i == 4 || i == 6)
            {
                combination_8[count_8] = 1;
                count_8++;

                if (combination_8[0] == 1 && combination_8[1] == 1 && combination_8[2] == 1)
                {
                    winner_number = strncmp(label, PLAYER_2, 1) == 0 ? '2' : '1';
                    break;
                }
            }
        }
    }

    return winner_number;
}
