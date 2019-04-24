#define GLUT_DISABLE_ATEXIT_HACK
#include "TSP.cpp"
#include <iostream>
#include <GL/glut.h>
#include <limits>
#include <assert.h>
#define KEY_ESC 27

using namespace std;

TSP *tsp = new TSP();
void displayGizmo()
{
    /*glBegin(GL_LINES);
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
    */
    glColor3d(0,0,255);
    glBegin(GL_QUADS);
        for(unsigned i=0;i < tsp->nodes.size();i++)
        {
            glVertex3f(tsp->nodes[i].first+0.45,tsp->nodes[i].second+0.45,0);
            glVertex3f(tsp->nodes[i].first-0.45,tsp->nodes[i].second+0.45,0);
            glVertex3f(tsp->nodes[i].first-0.45,tsp->nodes[i].second-0.45,0);
            glVertex3f(tsp->nodes[i].first+0.45,tsp->nodes[i].second-0.45,0);
        }
    glEnd();

    //cout<<"h _ "<<G->recorrido.size()<<endl;
    glBegin(GL_LINES);
    glColor3d(1.0 ,1.0, 1.0);
    for(int i=1;i<tsp->recorrido.size();i++)
    {
        glVertex2d(tsp->nodes[tsp->recorrido[i]].first,tsp->nodes[tsp->recorrido[i]].second);
        glVertex2d(tsp->nodes[tsp->recorrido[i-1]].first,tsp->nodes[tsp->recorrido[i-1]].second);
    }

		//glVertex2d(tsp->nodes[tsp->recorrido.size()-1].first,tsp->nodes[tsp->recorrido.size()-1].second);
        //glVertex2d(tsp->nodes[0].first,tsp->nodes[0].second);

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
    glutIdleFunc(&idle);

    //INICIA LAS OPERACIONES con un numero de iteraciones de 10000
	tsp->start(10000);

	glutMainLoop();
	return 0;
}
