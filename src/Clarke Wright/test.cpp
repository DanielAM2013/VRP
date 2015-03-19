#include <mathgl>

int sample(mglGraph *gr)
{
  mglData a;  mgls_prepare2d(&a);
  gr->SubPlot(2,2,0); gr->Title("Surf plot (default)");
  gr->Light(true);  gr->Rotate(50,60);  gr->Box();  gr->Surf(a);

  gr->SubPlot(2,2,1); gr->Title("'\\#' style; meshnum 10");
  gr->Rotate(50,60);  gr->Box();  gr->Surf(a,"#","meshnum 10");

  gr->SubPlot(2,2,2); gr->Title("'.' style");
  gr->Rotate(50,60);  gr->Box();  gr->Surf(a,".");

  gr->SubPlot(2,2,3); gr->Title("parametric form");
  mglData x(50,40),y(50,40),z(50,40);
  gr->Fill(x,"0.8*sin(pi*x)*sin(pi*(y+1)/2)");
  gr->Fill(y,"0.8*cos(pi*x)*sin(pi*(y+1)/2)");
  gr->Fill(z,"0.8*cos(pi*(y+1)/2)");
  gr->Rotate(50,60);  gr->Box();  gr->Surf(x,y,z,"BbwrR");
  return 0;
}
