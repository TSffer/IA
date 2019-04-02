#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <GL/glut.h>
#include "Grafo.cpp"
#define KEY_ESC 27

using namespace std;
static Grafo *G;
int inicio,destino;

void adaptRawPoint(int &x,int &y)
{
    x = x - 300;
    y = 300 - y;
}

void displayGizmo()
{
    glBegin(GL_LINES);
    glColor3d(255,0,0);
    //cout<<G->adj[0].size()<<endl;
        for(int i=0;i<G->adj.size();i++)
        {
           // cout<<"Gs"<<i<<endl;
            for(auto it = G->adj[i].begin();it != G->adj[i].end();it++)
            {
                glVertex2d(G->nodes[i].coord_x,G->nodes[i].coord_y);
                glVertex2d(G->nodes[it->first].coord_x,G->nodes[it->first].coord_y);
            }
        }
    glEnd();

    glColor3d(0,0,255);
    glBegin(GL_QUADS);
        for(unsigned i=0;i < G->nodes.size();i++)
        {
            glVertex3f(G->nodes[i].coord_x+0.45,G->nodes[i].coord_y+0.45,0);
            glVertex3f(G->nodes[i].coord_x-0.45,G->nodes[i].coord_y+0.45,0);
            glVertex3f(G->nodes[i].coord_x-0.45,G->nodes[i].coord_y-0.45,0);
            glVertex3f(G->nodes[i].coord_x+0.45,G->nodes[i].coord_y-0.45,0);
            //cout<<G->nodes[i].coord_x<<" "<<G->nodes[i].coord_y<<endl;
        }
    glEnd();

    //cout<<"h _ "<<G->recorrido.size()<<endl;
    glBegin(GL_LINES);
    glColor3d(1.0 ,1.0, 1.0);
    for(int i=1;i<G->recorrido.size();i++)
    {
        glVertex2d(G->nodes[G->recorrido[i]].coord_x,G->nodes[G->recorrido[i]].coord_y);
        glVertex2d(G->nodes[G->recorrido[i-1]].coord_x,G->nodes[G->recorrido[i-1]].coord_y);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3d(1, 1, 0.0);  // Nodo de inicio de color Amarillo
    glVertex2d(G->nodes[inicio].coord_x,G->nodes[inicio].coord_y);
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3d(0.5, 255, 0.0);  // Nodo de destino de color verde
    glVertex2d(G->nodes[destino].coord_x,G->nodes[destino].coord_y);
    glEnd();
}

void idle()
{
    glutPostRedisplay();
}

void glPaint(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();
    glOrtho(0,100,0,100,-1.0f,1.0f);
    
    displayGizmo();
    glutSwapBuffers();
}

void init_GL(void) 
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
GLvoid window_redraw(GLsizei width,GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,100,0,100,-1.0f,1.0f);
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600); 
    glutInitWindowPosition(400, 80); 
    glutCreateWindow("Grafo"); 
 
    init_GL(); 
 
    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    // Callback del teclado
    glutIdleFunc(&idle);

    G = new Grafo(500);
    G->crear_nodos();
    G->crear_edges();
    inicio = 4;
    destino = 9;
    G->A_star(inicio,destino);
    //G->busqueda_anchura(inicio,destino);
    glutMainLoop();
    return 0;
}