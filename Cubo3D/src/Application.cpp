

#include "stdafx.h"
#include "Application.h"


void Application::drawGeometry(const std::vector<Vec4>& Vertice, Tipo Dibujo)
{
	switch (Dibujo) //Qué voy a dibujar? 
	{
	case Application::Triangulos: 
		if (Vertice.size() <= 0) {
			return;
		}
		for (int i = 0; i < Vertice.size(); i += 3) {
			moveto(Vertice[i].b[0], Vertice[i].b[1]);
			lineto(Vertice[i + 1].b[0], Vertice[i + 1].b[1]);
			lineto(Vertice[i + 2].b[0], Vertice[i + 2].b[1]);
			lineto(Vertice[i].b[0], Vertice[i].b[1]);
		}

		break;
	case Application::Puntos:
		for (int a = 0; a < Vertice.size(); a++) {
			putPixel(Vertice[a].b[0], Vertice[a].b[1], 180, 255, 25, 255);
		}
		break;
	case Application::LINEA:
		for (int PrimerPunto = 0; PrimerPunto < Vertice.size()-1; PrimerPunto += 2) {
			moveto(Vertice[PrimerPunto].b[0], Vertice[PrimerPunto].b[1]);
			lineto(Vertice[PrimerPunto+1].b[0], Vertice[PrimerPunto+1].b[1]);
		}
		break;
	case Application::LineaStrip:
		moveto(Vertice[0].b[0], Vertice[0].b[1]);
		for (int PrimerPunto = 0; PrimerPunto < Vertice.size(); PrimerPunto++) {
			lineto(Vertice[PrimerPunto].b[0], Vertice[PrimerPunto].b[1]);
		}
		break;
	case Application::LINELOOP:
		moveto(Vertice[0].b[0], Vertice[0].b[1]);
		for (int PrimerPunto = 0; PrimerPunto < Vertice.size(); PrimerPunto++) {
			lineto(Vertice[PrimerPunto].b[0], Vertice[PrimerPunto].b[1]);
		}
		lineto(Vertice[0].b[0], Vertice[0].b[1]);
		break;
	case Application::TRIANGLESTRIP:
		moveto(Vertice[0].b[0], Vertice[0].b[1]);
		lineto(Vertice[1].b[0], Vertice[1].b[1]);
		lineto(Vertice[2].b[0], Vertice[2].b[1]);
		lineto(Vertice[0].b[0], Vertice[0].b[1]);
		for (int PrimerPunto = 3; PrimerPunto < Vertice.size(); PrimerPunto++) {
			lineto(Vertice[PrimerPunto-1].b[0], Vertice[PrimerPunto-1].b[1]);
			lineto(Vertice[PrimerPunto - 2].b[0], Vertice[PrimerPunto - 2].b[1]);
		}
		break;
	case Application::TRIANGLEFAN:
		moveto(Vertice[0].b[0], Vertice[0].b[1]);
		lineto(Vertice[1].b[0], Vertice[1].b[1]);
		lineto(Vertice[2].b[0], Vertice[2].b[1]);
		lineto(Vertice[0].b[0], Vertice[0].b[1]);
		for (int PrimerPunto = 3; PrimerPunto < Vertice.size(); PrimerPunto++) {
			moveto(Vertice[PrimerPunto].b[0], Vertice[PrimerPunto].b[1]);
			lineto(Vertice[PrimerPunto - 1].b[0], Vertice[PrimerPunto - 1].b[1]);
			moveto(Vertice[PrimerPunto].b[0], Vertice[PrimerPunto].b[1]);
			lineto(Vertice[0].b[0], Vertice[0].b[1]);
		}
		break;
	default:
		break;
	}
}

Application::Application(){
}

void Application::moveto(float x, float y) {
	posicionX = x;
	posicionY = y;
}

void Application::lineto(float x, float y) {
	line(posicionX, posicionY, x, y);
	moveto(x, y);
}

void Application::clearscren() {
	for (int a = 0; a < WIDTH; a++) {
		for (int b = 0; b < HEIGHT; b++) {
			putPixel(a-WIDTH/2, b-HEIGHT/2, 0, 0, 0, 0);
		}
	}
}


Application::~Application()
{
}

void Application::update()
{
	++angulo;
	Mat4 Rotarz = Mat4::RotarZ(angulo);
	Vec4 T1(300, 0, 0);
	Vec4 Escala(0.5, 0.5, 0.5);
	Mat4 Traslado = Mat4::Trasladar(T1.b[0], T1.b[1], T1.b[2]);
	Mat4 Rotarx = Mat4::RotarX(angulo * 5);
	Mat4 Rotary = Mat4::RotarY(angulo / 10);
	Mat4 escalo = Mat4::Escalar(Escala);
	Mat4 Acumulado = Rotarz*Traslado*Rotarx*Rotary*escalo;
	Mat4 Identidad;
	Vcopy2.clear();
	for (int i = 0; i < Vcopy.size(); i++) {
		Vcopy2.push_back(Acumulado*Vcopy[i]);
	}
}
void Application::draw()
{
	clearscren();
	drawGeometry(Vcopy2, Triangulos);
	drawGeometry(linea, LINEA);
	drawGeometry(LineStrip, LineaStrip);
	drawGeometry(LineLoop, LINELOOP);
	drawGeometry(TriangleStrip, TRIANGLESTRIP);
	drawGeometry(TriangleFan, TRIANGLEFAN);

}
void Application::setup()
{
	Vec4 a(-150, -150, 150), b(150, -150, 150), c(-150, 150, 150), d(150, 150, 150), e(-150, -150, -150), f(150, -150, -150), g(-150, 150, -150), h(150, 150, -150);
	Vec4 punto1(99,11,55);
	Vec4 punto2(88,22,66);
	Vec4 punto3(77,33,77);
	Vec4 punto4(66,44,88);
	Vec4 punto5(55, 55, 99);
	Vec4 punto6(44, 66, 11);
	Vec4 punto7(33, 77, 22);
	Vec4 punto8(22, 88, 33);
	Vec4 punto9(11, 99, 44);
	
	
	linea.push_back(punto1);
	linea.push_back(punto2);
	linea.push_back(punto3);
	linea.push_back(punto4);
	linea.push_back(punto5);
	linea.push_back(punto6);
	linea.push_back(punto7);
	linea.push_back(punto8); 
	linea.push_back(punto9);

	Vec4 puntoRepetido1(199, 11, 55);
	Vec4 puntoRepetido2(8, 22, 66);
	Vec4 puntoRepetido3(17, 33, 77);
	Vec4 puntoRepetido4(166, 44, 88);
	Vec4 puntoRepetido5(343, 55, 99);
	Vec4 puntoRepetido6(404, 66, 11);
	Vec4 puntoRepetido7(33, 177, 22);
	Vec4 puntoRepetido8(22, 188, 33);
	Vec4 puntoRepetido9(11, 199, 44);

	LineStrip.push_back(puntoRepetido1);
	LineStrip.push_back(puntoRepetido2);
	LineStrip.push_back(puntoRepetido3);
	LineStrip.push_back(puntoRepetido4);
	LineStrip.push_back(puntoRepetido5);
	LineStrip.push_back(puntoRepetido6);
	LineStrip.push_back(puntoRepetido7);
	LineStrip.push_back(puntoRepetido8);
	LineStrip.push_back(puntoRepetido9);

	Vec4 puntoRepetido11(19, 11, 55);
	Vec4 puntoRepetido21(89, 22, 66);
	Vec4 puntoRepetido31(170, 33, 77);
	Vec4 puntoRepetido41(16, 144, 88);
	Vec4 puntoRepetido51(33, 58, 99);
	Vec4 puntoRepetido61(40, 466, 11);
	Vec4 puntoRepetido71(303, 377, 22);
	Vec4 puntoRepetido81(220, 188, 33);
	Vec4 puntoRepetido91(111, 199, 44);

	LineLoop.push_back(puntoRepetido11);
	LineLoop.push_back(puntoRepetido21);
	LineLoop.push_back(puntoRepetido31);
	LineLoop.push_back(puntoRepetido41);
	LineLoop.push_back(puntoRepetido51);
	LineLoop.push_back(puntoRepetido61);
	LineLoop.push_back(puntoRepetido71);
	LineLoop.push_back(puntoRepetido81);
	LineLoop.push_back(puntoRepetido91);

	Vec4 puntoRepetido111(19, 11, 55);
	Vec4 puntoRepetido211(89, 22, 66);
	Vec4 puntoRepetido311(17, 33, 77);
	Vec4 puntoRepetido411(16, 14, 88);
	Vec4 puntoRepetido511(33, 58, 99);
	Vec4 puntoRepetido611(40, 46, 11);
	Vec4 puntoRepetido711(33, 37, 22);
	Vec4 puntoRepetido811(20, 18, 33);
	Vec4 puntoRepetido911(17, 19, 44);

	TriangleStrip.push_back(puntoRepetido111);
	TriangleStrip.push_back(puntoRepetido211);
	TriangleStrip.push_back(puntoRepetido311);
	TriangleStrip.push_back(puntoRepetido411);
	TriangleStrip.push_back(puntoRepetido511);
	TriangleStrip.push_back(puntoRepetido611);
	TriangleStrip.push_back(puntoRepetido711);
	TriangleStrip.push_back(puntoRepetido811);
	TriangleStrip.push_back(puntoRepetido911);

	Vec4 puntoRepetido1111(0, 0, 55);
	Vec4 puntoRepetido2111(100, 0, 66);
	Vec4 puntoRepetido3111(50, 50, 77);
	Vec4 puntoRepetido4111(-116, 42, 88);
	Vec4 puntoRepetido5111(-200, 18, 99);
	Vec4 puntoRepetido6111(-150, -30, 11);
	Vec4 puntoRepetido7111(133, -117, 22);
	Vec4 puntoRepetido8111(120, -138, 33);
	Vec4 puntoRepetido9111(117, -149, 44);

	TriangleFan.push_back(puntoRepetido1111);
	TriangleFan.push_back(puntoRepetido2111);
	TriangleFan.push_back(puntoRepetido3111);
	TriangleFan.push_back(puntoRepetido4111);
	TriangleFan.push_back(puntoRepetido5111);
	TriangleFan.push_back(puntoRepetido6111);
	TriangleFan.push_back(puntoRepetido7111);
	TriangleFan.push_back(puntoRepetido8111);
	TriangleFan.push_back(puntoRepetido9111);
	
	Vcopy.push_back(a);
	Vcopy.push_back(b);
	Vcopy.push_back(c);
	Vcopy.push_back(b);
	Vcopy.push_back(c);
	Vcopy.push_back(d);
	Vcopy.push_back(b);
	Vcopy.push_back(f);
	Vcopy.push_back(d);
	Vcopy.push_back(f);
	Vcopy.push_back(d);
	Vcopy.push_back(h);
	Vcopy.push_back(f);
	Vcopy.push_back(e);
	Vcopy.push_back(h);
	Vcopy.push_back(e);
	Vcopy.push_back(g);
	Vcopy.push_back(h);
	Vcopy.push_back(a);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(g);
	Vcopy.push_back(e);
	Vcopy.push_back(a);
	Vcopy.push_back(b);
	Vcopy.push_back(b);
	Vcopy.push_back(f);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(d);
	Vcopy.push_back(g);
	Vcopy.push_back(d);
	Vcopy.push_back(h);
	Vcopy.push_back(g);

}