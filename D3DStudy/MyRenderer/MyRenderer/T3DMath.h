#ifndef T3DMATH
#define T3DMATH


/**********************************************
*
* Name：数据结构和类型
* Usage：数学引擎需要的数据类型
*
**********************************************/
typedef struct VECTOR2D
{
	union 
	{
		float M[2];
		struct 
		{
			float x, y;
		};
	};
}VECTOR2D, POINT2D, *VECTOR2D_PTR, *POINT2D_PTR;

typedef struct VECTOR3D
{
	union
	{
		float M[3];
		struct
		{
			float x, y, z;
		};
	};
}VECTOR3D, POINT3D, *VECTOR3D_PTR, *POINT3D_PTR;


typedef struct VECTOR3D
{
	union
	{
		float M[4];
		struct
		{
			float x, y, z, w;
		};
	};
}VECTOR4D, POINT4D, *VECTOR4D_PTR, *POINT4D_PTR;

typedef struct VERTEX2DI
{
	int x, y;
}VERTEX2DI, *VERTEX2DI_PTR;
typedef struct VERTEX2DF
{
	int x, y;
}VERTEX2DF, *VERTEX2DF_PTR;


typedef struct PARMLINE2D
{
	POINT2D p0;//START
	POINT2D P1;//END
	VECTOR2D v;
}PARMLINE2D, *PARMLINE2D_PTR;

typedef struct PARMLINE2D
{
	POINT2D p0;//START
	POINT2D P1;//END
	VECTOR2D v;// |v| = |p0->p1|
}PARMLINE2D, *PARMLINE2D;
typedef struct PARMLINE3D
{
	POINT3D p0;//START
	POINT3D P1;//END
	VECTOR3D v;// |v| = |p0->p1|
}PARMLINE3D, *PARMLINE3D_PTR;

//点，法向量的模型
typedef struct PLANE3D
{
	POINT3D p0;
	VECTOR3D n;
}PLAN3D, *PLAN3D_PTR;

typedef struct  MATRIX4X4
{
	union 
	{
		float M[4][4];
		struct 
		{
			float M00, M01, M02, M03;
			float M10, M11, M12, M13;
			float M20, M21, M22, M23;
			float M30, M31, M32, M33;
		};
	};
}MATRIX4X4, *MATRIX4X4_PTR;
typedef struct  MATRIX4X3
{
	union
	{
		float M[4][3];
		struct
		{
			float M00, M01, M02;
			float M10, M11, M12;
			float M20, M21, M22;
			float M30, M31, M32;
		};
	};
}MATRIX4X3, *MATRIX4X3_PTR;
typedef struct  MATRIX1X4
{
	union
	{
		float M[1][4];
		struct
		{
			float M00, M01, M02, M03;
		};
	};
}MATRIX1X4, *MATRIX1X4_PTR;
typedef struct  MATRIX3X3
{
	union
	{
		float M[3][3];
		struct
		{
			float M00, M01, M02;
			float M10, M11, M12;
			float M20, M21, M22;
		};
	};
}MATRIX3X3, *MATRIX3X3_PTR;
typedef struct  MATRIX1X3
{
	union
	{
		float M[3];
		struct
		{
			float M00, M01, M02;
		};
	};
}MATRIX1X3, *MATRIX1X3_PTR;
typedef struct  MATRIX3X2
{
	union
	{
		float M[3][2];
		struct
		{
			float M00, M01;
			float M10, M11;
			float M20, M21;
		};
	};
}MATRIX3X2, *MATRIX3X2_PTR;
typedef struct  MATRIX2X2
{
	union
	{
		float M[2][2];
		struct
		{
			float M00, M01;
			float M10, M11;
		};
	};
}MATRIX2X2, *MATRIX2X2_PTR;
typedef struct  MATRIX1X2
{
	union
	{
		float M[1][2];
		struct
		{
			float M00, M01;
		};
	};
}MATRIX1X2, *MATRIX1X2_PTR;

//四元组
typedef struct QUAT
{
	union 
	{
		float M[4];
		struct 
		{
			float q0;
			VECTOR3D qv;
		};
		struct 
		{
			float w, x, y, z;
		};
	};
} QUAT, *QUAT_PTR;


/*
 *角坐标系
 */

//2D极坐标系
typedef struct
{
	float r;//半径
	float theta;//角度
} POLAR2D,*POLAR2D_PTR;
//3D柱面坐标
typedef struct
{
	float r;//半径
	float theta;//与z轴的夹角
	float z;//z坐标
} CYLINDRICAL3D,*CYLINDRICAL3D_PTR;
//3D球面坐标系
typedef struct
{
	float p;// 到原点的距离
	float theta;// 线段o->p和正z轴之间的夹角
	float phi;// 线段o->p在x-y平面上的投影与正x轴之间的夹角
} SPHERICAL3D,*SPHERICAL3D_PTR;

/*
 *定点数类型
 */
typedef int FIXP16;
typedef int *FIXP16_PTR;


/**********************************************
*
* Name：数学常量
* Usage：
*
**********************************************/

//与Pi相关的常量
#define PI	{(float)3.141592654f}
#define PI2	{(float)6.283185307f}
#define PI_DIV_2		{(float)1.570796327f}
#define PI_DIV_4		{(float)0.785398163f}
#define PI_INV			{(float)0.318309886f}
//与定点数运算相关的常量
#define FIXP16_SHIFT 16
#define FIXP16_MAG  65535
#define FIXP16_DP_MASK 0x0000ffff
#define FIXP16_WP_MASK 0xffff0000
#define FIXP16_ROUND_UP 0x00008000
//针对非常小的数的常量
#define EPSILON_E4 (FLOAT)(1E-4)
#define EPSILON_E5 (FLOAT)(1E-5)
#define EPSILON_E6 (FLOAT)(1E-6)
//用于参数化直线交点的常量
#define PARM_LINE_NO_INTERSECT	0
#define PARM_LINE_INTERSECT_IN_SEGMENT 1
#define PARM_LINE_INTERSECT_OUT_SEGMENT 2
#define PARM_LINE_INTERSECT_EVERYWHERE 3
//单位矩阵（用于简化矩阵的初始化）
const MATRIX4X4 IMAT_4X4 = { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
const MATRIX4X3 IMAT_4X3 = { 1,0,0,
0,1,0,
0,0,1,
0,0,0 };
const MATRIX3X3 IMAT_3X3 = { 1,0,0,
0,1,0,
0,0,1 };
const MATRIX2X2 IMAT_2X2 = { 1,0,
0,1 };


/**********************************************
*
* Name：宏和内联函数
* Usage：宏和内联函数比之函数调用的优势在于，省去了调用的开销。
*
**********************************************/


#endif // !2


