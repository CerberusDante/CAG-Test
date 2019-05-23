
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
#define Round(d) int(floor(d+0.5))

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

	//修改坐标系映射

	CDC *pDC = GetDC();
	CRect rect;											//定义矩形
	GetClientRect(&rect);								//获得客户去矩形的大小
	pDC->SetMapMode(MM_ANISOTROPIC);					//自定义坐标系映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());		//设置窗口比例
	pDC->SetViewportExt(rect.Width(), -rect.Height());	//设置视区比例，且x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
														//设置客户区中心为坐标原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
														//矩形与客户区重合
	srand((unsigned)time(NULL));

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
	
	{
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
		/*
			在这里插入画图代码段
		*/

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
		/*	
			在此处添加代码段
		*/
		pDC->SelectObject(pOldBrush);
		RedHatchBrush.DeleteObject();
	}		
	
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
	{
		CRect rect1(CPoint(-250, 50), CPoint(250, 150));
		CRect rect2(CPoint(-250, -150), CPoint(250, -50));
		CBrush Brush(HS_BDIAGONAL, RGB(255, 0, 0));//定义红色阴影画刷
		pDC->FillRect(&rect1, &Brush);//画刷填充
		pDC->FillSolidRect(&rect2, RGB(255, 0, 0));//红色填充
	}
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
	//绘制圆弧
	{
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
	}

	//绘制扇形函数
	{
		CBitmap NewBitmap;
		NewBitmap.LoadBitmap(IDB_INSTITUTE);
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
	}

	//绘制多边形函数
	{
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
