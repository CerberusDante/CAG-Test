
// 2DGraphicsView.cpp: CMy2DGraphicsView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2DGraphics.h"
#endif

#include "2DGraphicsDoc.h"
#include "2DGraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <math.h>
#define PI 3.1415926
#define Round(d) int(floor(d+0.5))//floor为取整函数，返回值是小于等于x的最大浮点数
#define Theta 180

// CMy2DGraphicsView

IMPLEMENT_DYNCREATE(CMy2DGraphicsView, CView)

BEGIN_MESSAGE_MAP(CMy2DGraphicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2DGraphicsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy2DGraphicsView 构造/析构

CMy2DGraphicsView::CMy2DGraphicsView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMy2DGraphicsView::~CMy2DGraphicsView()
{
}

BOOL CMy2DGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2DGraphicsView 绘图

void CMy2DGraphicsView::OnDraw(CDC* /*pDC*/)
{
	CMy2DGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC *pDC = GetDC();
	//修改坐标系映射
	CRect rect;											//定义矩形
	GetClientRect(&rect);								//获得客户去矩形的大小
	pDC->SetMapMode(MM_ANISOTROPIC);					//自定义坐标系映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());		//设置窗口比例
	pDC->SetViewportExt(rect.Width(), -rect.Height());	//设置视区比例，且x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	//设置客户区中心为坐标原点
	//矩形与客户区重合
	srand((unsigned)time(NULL));
	
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	/*for (int x = 200; x <= 233; x++) {
		for (int y = 300; y <= 333; y++)
		{
			CPoint P(x, y);
			pDC->SetPixelV(x, y, RGB(255, 0, 0));
		}
	}

	int a, b;
	COLORREF crColor;
	for (a = -50; a < 50; a++)
	{
		for (b = -150; b < -50; b++)
		{
			pDC->SetPixelV(b, a, RGB(rand() % 255, rand() % 255, rand() % 255));
		}
	}

	for (a = -50; a < 50; a++)
	{
		for (b = -150; b < -50; b++)
		{
			crColor = pDC->GetPixel(b, a);
			pDC->SetPixelV(-b, a, crColor);
		}
	}*/

	/*{
		pDC->SetPixelV(200, 300, RGB(255, 0, 0));
		// 在坐标200，300 画点，RGB为红色
	}

	{
		pDC->MoveTo(100, 100);
		pDC->LineTo(200, 300);
		// 从(100, 100)到(200,300) 画直线
	}

	{
		CPen RedPen, *pOldPen;
		RedPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		pOldPen = pDC->SelectObject(&RedPen);
		
			//在这里插入画图代码段
	

		pDC->SelectObject(pOldPen);
		RedPen.DeleteObject();
		//创建红色画笔，宽度为2
	}

	{
		CPen BluePen, *qOldPen;
		BluePen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		qOldPen = pDC->SelectObject(&BluePen);

		pDC->MoveTo(50, 20);
		pDC->LineTo(200, 100);

		pDC->MoveTo(-50, 20);
		pDC->LineTo(-200, 100);

		pDC->SelectObject(qOldPen);
		BluePen.DeleteObject();


		pDC->Rectangle(100, 100, 400, 300);
		pDC->Ellipse(100, 100, 400, 300);
	}

	{
		//画刷函数
		CBrush RedSolidBrush, RedHatchBrush, *pOldBrush;
		//SolidBrush —— 实心画刷
		//HatchBrush —— 空心画刷

		//实心画刷
		RedSolidBrush.CreateSolidBrush(RGB(255, 0, 0));
		pOldBrush = pDC->SelectObject(&RedSolidBrush);

		pDC->Ellipse(45, 15, 55, 25);
		pDC->Ellipse(195, 95, 205, 105);

		pDC->Ellipse(-45, 15, -55, 25);
		pDC->Ellipse(-195, 95, -205, 105);

		pDC->SelectObject(pOldBrush);
		RedSolidBrush.DeleteObject();

		//空心画刷
		RedHatchBrush.CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
		pOldBrush = pDC->SelectObject(&RedHatchBrush);
		
			//在此处添加代码段
		
		pDC->SelectObject(pOldBrush);
		RedHatchBrush.DeleteObject();
	}*/

	//绘制圆角矩形并填充
	{
		/*rect.DeflateRect(100, 100);//将矩形两个方向都缩小100个像素
		CPen NewPen, *pOldPen;
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		pOldPen = pDC->SelectObject(&NewPen);
		pDC->Rectangle(rect);
		CBrush NewBrush, *pOldBrush;
		NewBrush.CreateSolidBrush(RGB(255, 0, 0));
		pOldBrush = pDC->SelectObject(&NewBrush);
		pDC->RoundRect(rect, CPoint(200, 200));//绘制圆角矩形
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);*/
	}
	//填充矩形
	/*{
		CRect rect1(CPoint(-250, 50), CPoint(250, 150));
		CRect rect2(CPoint(-250, -150), CPoint(250, -50));
		CBrush Brush(HS_BDIAGONAL, RGB(255, 0, 0));//定义红色阴影画刷
		pDC->FillRect(&rect1, &Brush);//画刷填充
		pDC->FillSolidRect(&rect2, RGB(255, 0, 0));//红色填充
	}*/
	//绘制椭圆
	{
		/*rect.DeflateRect(100, 100);
		CBrush *pOldBrush;
		pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);//选择透明画刷
		int r = rect.Height() / 2;								//定义圆的半径
		CRect rect1(CPoint(-r, -r), CPoint(r, r));				//定义圆的外接矩形
		pDC->Ellipse(rect1);									//绘制圆
		pDC->Ellipse(rect);										//绘制椭圆
		pDC->Rectangle(rect);									//绘制外接矩形
		pDC->SelectObject(pOldBrush);*/
	}
	//绘制圆弧,12点到3点使用蓝色画笔绘制，其余部分使用点划线绘制
	/*{
		CPoint Twelve(0, rect.Height() / 2), Three(rect.Width() / 2, 0);
		CPen penBlack, penBlue, *pOldPen;
		penBlue.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		penBlack.CreatePen(PS_DASHDOT, 1, RGB(0, 0, 0));
		pDC->SetArcDirection(AD_CLOCKWISE);
		pOldPen = pDC->SelectObject(&penBlue);
		pDC->Arc(rect, Twelve, Three);
		pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
		pOldPen = pDC->SelectObject(&penBlack);
		pDC->Arc(rect, Twelve, Three);
		pDC->SelectObject(pOldPen);
	}*/

	//绘制扇形函数
	/*{
		CBitmap NewBitmap;
		NewBitmap.LoadBitmap(IDB_INSTITUTE);			//添加资源文件并设置ID，设为画刷
		CBrush NewBrush, *pOldBrush;
		NewBrush.CreatePatternBrush(&NewBitmap);
		pOldBrush = pDC->SelectObject(&NewBrush);
		CPen *pOldPen;
		pOldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);
		CPoint ld, rt, sp, ep;
		ld = CPoint(-400, -600), rt = CPoint(400, 200);//外接矩形的左下角点ld、右下角点rt
		sp = CPoint(400, 0), ep = CPoint(-400, 0);		//椭圆弧的起点sp和终点ep
		pDC->Pie(CRect(ld, rt), sp, ep);
		pDC->SelectObject(pOldBrush);
		NewBitmap.DeleteObject();
		ld = CPoint(-80, -280), rt = CPoint(80, -120);
		sp = CPoint(400, 0), ep = CPoint(-400, 0);
		pDC->Pie(CRect(ld, rt), sp, ep);				//使用默认画刷填充
		pDC->SelectObject(pOldPen);
	}*/

	//绘制多边形函数
	/*{
		CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));
		CPen *pOldPen = pDC->SelectObject(&penBlue);
		CBrush brushRed(RGB(255, 0, 0));
		CBrush *pOldBrush = pDC->SelectObject(&brushRed);
		pDC->SetPolyFillMode(WINDING);
		int r = 200;
		CPoint p[5];
		double Beta = 2 * PI / 5;
		double Alpha = PI / 10;
		for (int i = 0; i < 5; i++)
		{
			p[i].x = Round(r*cos(i*Beta + Alpha));//计算正五边形顶点坐标
			p[i].y = Round(r*sin(i*Beta + Alpha));
		}
		CPoint v[5];							//定义五角星顶点数组
		v[0] = p[0]; v[1] = p[2];
		v[2] = p[4]; v[3] = p[1];
		v[4] = p[3];							//转储顶点
		pDC->Polygon(v, 5);						//绘制五角星
		pDC->SelectObject(pOldPen);				//恢复画笔
		pDC->SelectObject(pOldBrush);			//恢复画刷
	}*/


	//路径层函数，第一个多边形路径层函数填充不绘制边界线，另一个多边形绘制边界线
	/*{
		CPoint p[7];											//定义顶点坐标数组
		p[0] = CPoint(-160, 20); p[1] = CPoint(-240, 100);
		p[2] = CPoint(-280, 0); p[3] = CPoint(-240, -100);
		p[4] = CPoint(-180, -40); p[5] = CPoint(-140, -100);
		p[6] = CPoint(-60, 40);
		CBrush NewBrush;
		NewBrush.CreateSolidBrush(RGB(255, 0, 0));
		CBrush *pOldBrush = pDC->SelectObject(&NewBrush);
		pDC->BeginPath();
		pDC->MoveTo(p[0]);										//绘制左侧多边形
		for (int i = 1; i < 7; i++)
		{
			pDC->LineTo(p[i]);
		}
		pDC->LineTo(p[0]);
		pDC->EndPath();
		pDC->FillPath();										//FillPath填充路径层
		p[0] = CPoint(200, 20); p[1] = CPoint(120, 100);
		p[2] = CPoint(80, 0); p[3] = CPoint(120, -100);
		p[4] = CPoint(180, -40); p[5] = CPoint(220, -100);
		p[6] = CPoint(300, 40);
		pDC->BeginPath();
		pDC->MoveTo(p[0]);										//绘制右侧多边形
		for (int i = 1; i < 7; i++)
		{
			pDC->LineTo(p[i]);
		}
		pDC->LineTo(p[0]);
		pDC->EndPath();
		pDC->StrokeAndFillPath();								//StrokeAndFillPath填充路径层
		pDC->SelectObject(pOldBrush);
		NewBrush.DeleteObject();
	}*/

	//绘制Bezier样条函数
	//拼接的两段Bezier样条曲线
	/*{
		CPoint p[7];											//定义顶点坐标数组
		p[0] = CPoint(-350, -100); p[1] = CPoint(-250, 100);
		p[2] = CPoint(0, 130); p[3] = CPoint(50, -50);

		double k = (p[3].y - p[2].y) / (p[3].x - p[2].x);		//计算参数k
		double x = 90, y = k * (x - p[3].x) + p[3].y;			//计算拼接点p[4]的坐标

		p[4] = CPoint(Round(x), Round(y)); p[5] = CPoint(350, -20);
		p[6] = CPoint(250, 130);
		for (int i = 0; i < 7; i++)
		{
			if (0 == i)
				pDC->MoveTo(p[i]);
			else
				pDC->LineTo(p[i]);
			pDC->Ellipse(p[i].x - 5, p[i].y - 5, p[i].x + 5, p[i].y + 5);
													//黑色实心圆绘制控制点
		}
		CPen NewPen, *pOldPen;
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));	//蓝色画笔绘制样条曲线
		pOldPen = pDC->SelectObject(&NewPen);
		pDC->PolyBezier(p, 7);							//绘制Bezier样条
		pDC->SelectObject(pOldPen);
	}*/

	//位图操作函数，在客户区中央显示图片
	/*{
		CDC memDC;												//声明一个内存DC
		memDC.CreateCompatibleDC(pDC);							//创建一个与显示DC兼容的内存DC
		CBitmap NewBitmap, *pOldBitmap;
		NewBitmap.LoadBitmap(IDB_INSTITUTE);					//从资源中导入位图
		BITMAP bmpInfo;											//声明bmpInfo结构体
		NewBitmap.GetBitmap(&bmpInfo);							//获取位图信息
		pOldBitmap = memDC.SelectObject(&NewBitmap);			//将位图选入内存DC
		memDC.SetMapMode(MM_ANISOTROPIC);						//内存DC自定义坐标系
		memDC.SetWindowExt(bmpInfo.bmWidth, bmpInfo.bmHeight);
		memDC.SetViewportExt(bmpInfo.bmWidth, -bmpInfo.bmHeight);
		memDC.SetViewportOrg(bmpInfo.bmWidth / 2, bmpInfo.bmHeight / 2);
		int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
																//计算位图在客户区的中心点
		int nY = rect.top + (rect.Height() - bmpInfo.bmWidth) / 2;
		pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC,
			-bmpInfo.bmWidth / 2, -bmpInfo.bmHeight / 2, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
								//StretchBlt函数将位图拉伸至整个客户区，位图像素增大，图像变得模糊
																//将内存DC中的位图复制到设备DC
		memDC.SelectObject(pOldBitmap);							//从内存中释放位图
	}*/

	//文本函数
	/*{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(RGB(255, 255, 0));
		pDC->TextOut(-200, 20, "Computer Graphics Based On Visual Studio 2017!");
		CString data, str = "BoChuang Research Institute";
		data.Format("%s",str);
		pDC->TextOutW(50, 20, data);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		int i1 = 5, i2 = 8;
		double d1 = 5.2, d2 = 8.3;
		data.Format("%d,%d", i1, i2);
		pDC->TextOut(-200, -20, data);
		data.Format("%f,%f", d1, d2);
		pDC->TextOutW(0, -20, data);
	}*/

	//双缓冲机制
	{
		CRect rect;											//定义矩形
		GetClientRect(&rect);								//获得客户去矩形的大小
		pDC->SetMapMode(MM_ANISOTROPIC);					//自定义坐标系映射模式
		pDC->SetWindowExt(rect.Width(), rect.Height());		//设置窗口比例
		pDC->SetViewportExt(rect.Width(), -rect.Height());	//设置视区比例，且x轴水平向右，y轴垂直向上
		pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
		//设置客户区中心为坐标原点
		//矩形与客户区重合
		srand((unsigned)time(NULL));
		CDC memDC;											//声明内存DC
		CBitmap NewBitmap, *pOldBitmap;	
		memDC.CreateCompatibleDC(pDC);						//创建一个与显示DC兼容的内存DC
		NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
															//创建兼容内存位图
		pOldBitmap = memDC.SelectObject(&NewBitmap);		//将兼容位图选入内存DC
		memDC.FillSolidRect(rect, pDC->GetBkColor());
															//按原来的背景色填充客户区，否则是黑色
		rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);


		memDC.SetMapMode(MM_ANISOTROPIC);					//内存DC自定义坐标系
		memDC.SetWindowExt(rect.Width(), rect.Height());	
		memDC.SetViewportExt(rect.Width(), -rect.Height());
		memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
		DrawObject(&memDC);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
	}
}



// CMy2DGraphicsView 打印


void CMy2DGraphicsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2DGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2DGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2DGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy2DGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2DGraphicsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// 绘制阴阳鱼
void CMy2DGraphicsView::DrawObject(CDC * pDC)
{
	CPen NewPen, *pOldPen;
	CBrush NewBrush, *pOldBrush;
	long R = 300;
	CPoint ld, rt, as, ae;
	//ld(left down)左下角点， rt(right top)右上角点
	//as(arc start)圆弧起点， ae(arc end)圆弧终点
	//绘制黑色半圆
	NewBrush.CreateSolidBrush(RGB(0, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	ld = CPoint(-R, -R); rt = CPoint(R, R);
	as = CPoint(Round(R*cos((Theta - 90)*PI / 180)), Round(R*sin((Theta - 90)*PI / 180)));
	ae = CPoint(Round(R*cos((Theta + 90)*PI / 180)), Round(R*sin((Theta + 90)*PI / 180)));

	pDC->Pie(CRect(ld, rt), as, ae);
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
	//绘制白色半圆
	NewBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldBrush = pDC->SelectObject(&NewBrush);
	ld = CPoint(-R, -R); rt = CPoint(R, R);
	as = CPoint(Round(R*cos((Theta + 90)*PI / 180)), Round(R*sin((Theta + 90)*PI / 180)));
	ae = CPoint(Round(R*cos((Theta - 90)*PI / 180)), Round(R*sin((Theta - 90)*PI / 180)));
	pDC->Pie(CRect(ld, rt), as, ae);
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
	//绘制白色鱼头
	long r = R / 2;
	NewPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	pOldPen = pDC->SelectObject(&NewPen);
	ld = CPoint(Round(r*cos((Theta + 90)*PI / 180) - r), Round(r*sin((Theta + 90)*PI / 180) - r));
	rt = CPoint(Round(r*cos((Theta + 90)*PI / 180) + r), Round(r*sin((Theta + 90)*PI / 180) + r));
	pDC->Ellipse(CRect(ld, rt));
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	//绘制黑色鱼头
	NewBrush.CreateSolidBrush(RGB(0, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	ld = CPoint(Round(r*cos((Theta - 90)*PI / 180) - r), Round(r*sin((Theta - 90)*PI / 180) - r));
	rt = CPoint(Round(r*cos((Theta - 90)*PI / 180) + r), Round(r*sin((Theta - 90)*PI / 180) + r));
	pDC->Ellipse(CRect(ld, rt));
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
	//绘制黑色鱼眼
	long r1 = R / 8;
	NewBrush.CreateSolidBrush(RGB(0, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	ld = CPoint(Round(r*cos((Theta + 90)*PI / 180) - r1), Round(r*sin((Theta + 90)*PI / 180) - r1));
	rt = CPoint(Round(r*cos((Theta + 90)*PI / 180) + r1), Round(r*sin((Theta + 90)*PI / 180) + r1));
	pDC->Ellipse(CRect(ld, rt));
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
	//绘制白色鱼眼
	NewPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	pOldPen = pDC->SelectObject(&NewPen);
	ld = CPoint(Round(r*cos((Theta - 90)*PI / 180) - r1), Round(r*sin((Theta - 90)*PI / 180) - r1));
	rt = CPoint(Round(r*cos((Theta - 90)*PI / 180) + r1), Round(r*sin((Theta - 90)*PI / 180) + r1));
	pDC->Ellipse(CRect(ld, rt));
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}


// CMy2DGraphicsView 诊断

#ifdef _DEBUG
void CMy2DGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2DGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2DGraphicsDoc* CMy2DGraphicsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2DGraphicsDoc)));
	return (CMy2DGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2DGraphicsView 消息处理程序




