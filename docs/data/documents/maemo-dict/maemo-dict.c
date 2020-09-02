#include <hildon/hildon-program.h>
#include <gtk/gtkmain.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

GtkEntry* input;
GtkTextView* output;
GtkTextBuffer* text;
GtkButton* go;

void generate (GtkButton* g, gpointer p)
{
  {
    GtkTextIter end;
    GtkTextIter start;
    gtk_text_buffer_get_end_iter(text, &end);
    gtk_text_buffer_get_start_iter(text, &start);
    gtk_text_buffer_delete(text, &start, &end);
  }


  //g_print ("coin\n");

  int pipefd[2];
  pipe(pipefd);

  pid_t f = fork();
  //g_print("tata\n");

  if (f == 0)
    {
      //child
      close(pipefd[0]);
      close(1);
      close(2);
      dup2(pipefd[1],1);
      dup2(pipefd[1],2);
      close(pipefd[1]);

      const gchar* word = gtk_entry_get_text(input);

      char* arg[3];
      arg[0] = "dict";
      arg[1] = (char*)word;
      arg[2] = NULL;

      execvp ("dict", arg);

      //g_print("toto2\n");
      exit(0);
    }
  else
    {
      //father
      close(pipefd[1]);
      char buffer[1024];
      int s;

      while ((s = read (pipefd[0],buffer, 1024)))
	{
	  GtkTextIter end;
	  gtk_text_buffer_get_end_iter(text, &end);
	  gtk_text_buffer_insert(text, &end, buffer, s);
	}
      close(pipefd[0]);
      wait (&s);
      //g_print("done\n");
    }

}

int main(int argc, char *argv[])
{
    /* Create needed variables */
    HildonProgram *program;
    HildonWindow *window;

    /* Initialize the GTK. */
    gtk_init(&argc, &argv);

    /* Create the Hildon program and setup the title */
    program = HILDON_PROGRAM(hildon_program_get_instance());
    g_set_application_name("Dict Frontend");

    /* Create HildonWindow and set it to HildonProgram */
    window = HILDON_WINDOW(hildon_window_new());
    hildon_program_add_window(program, window);

    //    lm = GTK_CONTAINER(gtk_vpaned_new());
    GtkContainer* lv = GTK_CONTAINER(gtk_vpaned_new());
    GtkContainer* lh = GTK_CONTAINER(gtk_hpaned_new());
    input = GTK_ENTRY(gtk_entry_new());
    output = GTK_TEXT_VIEW(gtk_text_view_new());
    text = GTK_TEXT_BUFFER(gtk_text_view_get_buffer (output));
    go = GTK_BUTTON(gtk_button_new_with_label("go"));

    gtk_text_view_set_editable (output,FALSE);

    g_signal_connect(G_OBJECT(go), "clicked", G_CALLBACK(generate), NULL);

    gtk_container_add(GTK_CONTAINER(window),
                      GTK_WIDGET(lv));



    /* Add example label to window */

    GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(scroll),
                      GTK_WIDGET(output));

    gtk_container_add(GTK_CONTAINER(lh),
                      GTK_WIDGET(input));

    gtk_container_add(GTK_CONTAINER(lh),
                      GTK_WIDGET(go));

    gtk_container_add(GTK_CONTAINER(lv),
                      GTK_WIDGET(lh));


    gtk_container_add(GTK_CONTAINER(lv),
                      GTK_WIDGET(scroll));

    gtk_paned_set_position (GTK_PANED(lh), 500);



    /* Begin the main application */
    gtk_widget_show_all(GTK_WIDGET(window));

    /* Connect signal to X in the upper corner */
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    /* Exit */
    return 0;
}
