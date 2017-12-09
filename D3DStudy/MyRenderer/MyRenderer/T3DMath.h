#ifndef T3DMATH
#define T3DMATH


/**********************************************
*
* Name�����ݽṹ������
* Usage����ѧ������Ҫ����������
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

//�㣬��������ģ��
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

//��Ԫ��
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
 *������ϵ
 */

//2D������ϵ
typedef struct
{
	float r;//�뾶
	float theta;//�Ƕ�
} POLAR2D,*POLAR2D_PTR;
//3D��������
typedef struct
{
	float r;//�뾶
	float theta;//��z��ļн�
	float z;//z����
} CYLINDRICAL3D,*CYLINDRICAL3D_PTR;
//3D��������ϵ
typedef struct
{
	float p;// ��ԭ��ľ���
	float theta;// �߶�o->p����z��֮��ļн�
	float phi;// �߶�o->p��x-yƽ���ϵ�ͶӰ����x��֮��ļн�
} SPHERICAL3D,*SPHERICAL3D_PTR;

/*
 *����������
 */
typedef int FIXP16;
typedef int *FIXP16_PTR;


/**********************************************
*
* Name����ѧ����
* Usage��
*
**********************************************/

//��Pi��صĳ���
#define PI	{(float)3.141592654f}
#define PI2	{(float)6.283185307f}
#define PI_DIV_2		{(float)1.570796327f}
#define PI_DIV_4		{(float)0.785398163f}
#define PI_INV			{(float)0.318309886f}
//�붨����������صĳ���
#define FIXP16_SHIFT 16
#define FIXP16_MAG  65535
#define FIXP16_DP_MASK 0x0000ffff
#define FIXP16_WP_MASK 0xffff0000
#define FIXP16_ROUND_UP 0x00008000
//��Էǳ�С�����ĳ���
#define EPSILON_E4 (FLOAT)(1E-4)
#define EPSILON_E5 (FLOAT)(1E-5)
#define EPSILON_E6 (FLOAT)(1E-6)
//���ڲ�����ֱ�߽���ĳ���
#define PARM_LINE_NO_INTERSECT	0
#define PARM_LINE_INTERSECT_IN_SEGMENT 1
#define PARM_LINE_INTERSECT_OUT_SEGMENT 2
#define PARM_LINE_INTERSECT_EVERYWHERE 3
//��λ�������ڼ򻯾���ĳ�ʼ����
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
* Name�������������
* Usage���������������֮�������õ��������ڣ�ʡȥ�˵��õĿ�����
*
**********************************************/


#endif // !2


