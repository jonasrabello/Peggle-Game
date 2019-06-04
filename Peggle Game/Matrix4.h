#pragma once


#include <string>
#include <sstream>
#include "Vector3.h"


struct Matrix4
{
	// Members
	float data[ 16 ];

	// Constructors
	inline Matrix4()
	{
		SetIdentity();
	}
	inline Matrix4( const Matrix4& other )
	{
		Set( other );
	}
	inline Matrix4( float x0, float x1, float x2, float x3,
					float y0, float y1, float y2, float y3,
					float z0, float z1, float z2, float z3,
					float w0, float w1, float w2, float w3 )
	{
		Set(
			x0, x1, x2, x3,
			y0, y1, y2, y3,
			z0, z1, z2, z3,
			w0, w1, w2, w3
		);
	}

	// Properties
	inline Matrix4 Inverse() const
	{
		Matrix4 inverse;

		inverse.data[ 0 ] =   data[  5 ] * data[ 10 ] * data[ 15 ] - data[  5 ] * data[ 11 ] * data[ 14 ] -
								data[  9 ] * data[  6 ] * data[ 15 ] + data[  9 ] * data[  7 ] * data[ 14 ] +
								data[ 13 ] * data[  6 ] * data[ 11 ] - data[ 13 ] * data[  7 ] * data[ 10 ];
		inverse.data[ 1 ] =  -data[  1 ] * data[ 10 ] * data[ 15 ] + data[  1 ] * data[ 11 ] * data[ 14 ] +
								data[  9 ] * data[  2 ] * data[ 15 ] - data[  9 ] * data[  3 ] * data[ 14 ] -
								data[ 13 ] * data[  2 ] * data[ 11 ] + data[ 13 ] * data[  3 ] * data[ 10 ];
		inverse.data[ 2 ] =   data[  1 ] * data[  6 ] * data[ 15 ] - data[  1 ] * data[  7 ] * data[ 14 ] -
								data[  5 ] * data[  2 ] * data[ 15 ] + data[  5 ] * data[  3 ] * data[ 14 ] +
								data[ 13 ] * data[  2 ] * data[  7 ] - data[ 13 ] * data[  3 ] * data[  6 ];
		inverse.data[ 3 ] =  -data[  1 ] * data[  6 ] * data[ 11 ] + data[  1 ] * data[  7 ] * data[ 10 ] +
								data[  5 ] * data[  2 ] * data[ 11 ] - data[  5 ] * data[  3 ] * data[ 10 ] -
								data[  9 ] * data[  2 ] * data[  7 ] + data[  9 ] * data[  3 ] * data[  6 ];
		inverse.data[ 4 ] =  -data[  4 ] * data[ 10 ] * data[ 15 ] + data[  4 ] * data[ 11 ] * data[ 14 ] +
								data[  8 ] * data[  6 ] * data[ 15 ] - data[  8 ] * data[  7 ] * data[ 14 ] -
								data[ 12 ] * data[  6 ] * data[ 11 ] + data[ 12 ] * data[  7 ] * data[ 10 ];
		inverse.data[ 5 ] =   data[  0 ] * data[ 10 ] * data[ 15 ] - data[  0 ] * data[ 11 ] * data[ 14 ] -
								data[  8 ] * data[  2 ] * data[ 15 ] + data[  8 ] * data[  3 ] * data[ 14 ] +
								data[ 12 ] * data[  2 ] * data[ 11 ] - data[ 12 ] * data[  3 ] * data[ 10 ];
		inverse.data[ 6 ] =  -data[  0 ] * data[  6 ] * data[ 15 ] + data[  0 ] * data[  7 ] * data[ 14 ] +
								data[  4 ] * data[  2 ] * data[ 15 ] - data[  4 ] * data[  3 ] * data[ 14 ] -
								data[ 12 ] * data[  2 ] * data[  7 ] + data[ 12 ] * data[  3 ] * data[  6 ];
		inverse.data[ 7 ] =   data[  0 ] * data[  6 ] * data[ 11 ] - data[  0 ] * data[  7 ] * data[ 10 ] -
								data[  4 ] * data[  2 ] * data[ 11 ] + data[  4 ] * data[  3 ] * data[ 10 ] +
								data[  8 ] * data[  2 ] * data[  7 ] - data[  8 ] * data[  3 ] * data[  6 ];
		inverse.data[ 8 ] =   data[  4 ] * data[  9 ] * data[ 15 ] - data[  4 ] * data[ 11 ] * data[ 13 ] -
								data[  8 ] * data[  5 ] * data[ 15 ] + data[  8 ] * data[  7 ] * data[ 13 ] +
								data[ 12 ] * data[  5 ] * data[ 11 ] - data[ 12 ] * data[  7 ] * data[  9 ];
		inverse.data[ 9 ] =  -data[  0 ] * data[  9 ] * data[ 15 ] + data[  0 ] * data[ 11 ] * data[ 13 ] +
								data[  8 ] * data[  1 ] * data[ 15 ] - data[  8 ] * data[  3 ] * data[ 13 ] -
								data[ 12 ] * data[  1 ] * data[ 11 ] + data[ 12 ] * data[  3 ] * data[  9 ];
		inverse.data[ 10 ] =  data[  0 ] * data[  5 ] * data[ 15 ] - data[  0 ] * data[  7 ] * data[ 13 ] -
								data[  4 ] * data[  1 ] * data[ 15 ] + data[  4 ] * data[  3 ] * data[ 13 ] +
								data[ 12 ] * data[  1 ] * data[  7 ] - data[ 12 ] * data[  3 ] * data[  5 ];
		inverse.data[ 11 ] = -data[  0 ] * data[  5 ] * data[ 11 ] + data[  0 ] * data[  7 ] * data[  9 ] +
								data[  4 ] * data[  1 ] * data[ 11 ] - data[  4 ] * data[  3 ] * data[  9 ] -
								data[  8 ] * data[  1 ] * data[  7 ] + data[  8 ] * data[  3 ] * data[  5 ];
		inverse.data[ 12 ] = -data[  4 ] * data[  9 ] * data[ 14 ] + data[  4 ] * data[ 10 ] * data[ 13 ] +
								data[  8 ] * data[  5 ] * data[ 14 ] - data[  8 ] * data[  6 ] * data[ 13 ] -
								data[ 12 ] * data[  5 ] * data[ 10 ] + data[ 12 ] * data[  6 ] * data[  9 ];
		inverse.data[ 13 ] =  data[  0 ] * data[  9 ] * data[ 14 ] - data[  0 ] * data[ 10 ] * data[ 13 ] -
								data[  8 ] * data[  1 ] * data[ 14 ] + data[  8 ] * data[  2 ] * data[ 13 ] +
								data[ 12 ] * data[  1 ] * data[ 10 ] - data[ 12 ] * data[  2 ] * data[  9 ];
		inverse.data[ 14 ] = -data[  0 ] * data[  5 ] * data[ 14 ] + data[  0 ] * data[  6 ] * data[ 13 ] +
								data[  4 ] * data[  1 ] * data[ 14 ] - data[  4 ] * data[  2 ] * data[ 13 ] -
								data[ 12 ] * data[  1 ] * data[  6 ] + data[ 12 ] * data[  2 ] * data[  5 ];
		inverse.data[ 15 ] =  data[  0 ] * data[  5 ] * data[ 10 ] - data[  0 ] * data[  6 ] * data[  9 ] -
								data[  4 ] * data[  1 ] * data[ 10 ] + data[  4 ] * data[  2 ] * data[  9 ] +
								data[  8 ] * data[  1 ] * data[  6 ] - data[  8 ] * data[  2 ] * data[  5 ];

		float determinant = 
			data[ 0 ] * inverse.data[  0 ] + 
			data[ 1 ] * inverse.data[  4 ] +
			data[ 2 ] * inverse.data[  8 ] + 
			data[ 3 ] * inverse.data[ 12 ];

		return inverse / determinant;
	}
	inline Matrix4 Transpose() const
	{
		return Matrix4(
			data[  0 ], data[  4 ], data[  8 ], data[ 12 ],
			data[  1 ], data[  5 ], data[  9 ], data[ 13 ],
			data[  2 ], data[  6 ], data[ 10 ], data[ 14 ],
			data[  3 ], data[  7 ], data[ 11 ], data[ 15 ]
		);
	}

	// Math operations
	inline Matrix4 DivideBy( float other ) const
	{
		float inverseOther = 1.0f / other;
		return Multiply( inverseOther );
	}
	inline Matrix4 Multiply( float other ) const
	{
		return Matrix4(
			other * data[  0 ], other * data[  1 ], other * data[  2 ], other * data[  3 ],
			other * data[  4 ], other * data[  5 ], other * data[  6 ], other * data[  7 ],
			other * data[  8 ], other * data[  9 ], other * data[ 10 ], other * data[ 11 ],
			other * data[ 12 ], other * data[ 13 ], other * data[ 14 ], other * data[ 15 ]
		);
	}
	inline Vector3 Multiply( const Vector3& other ) const
	{
		return Vector3(
			other.x * data[ 0 ] + other.y * data[ 4 ] + other.z * data[  8 ] + 1.0f * data[ 12 ],
			other.x * data[ 1 ] + other.y * data[ 5 ] + other.z * data[  9 ] + 1.0f * data[ 13 ],
			other.x * data[ 2 ] + other.y * data[ 6 ] + other.z * data[ 10 ] + 1.0f * data[ 14 ]
		);
	}
	inline Matrix4 Multiply( const Matrix4& other ) const
	{
		return Matrix4( 
			data[ 0 * 4 + 0 ] * other.data[ 0 * 4 + 0 ] + data[ 0 * 4 + 1 ] * other.data[ 1 * 4 + 0 ] + data[ 0 * 4 + 2 ] * other.data[ 2 * 4 + 0 ] + data[ 0 * 4 + 3 ] * other.data[ 3 * 4 + 0 ],
			data[ 0 * 4 + 0 ] * other.data[ 0 * 4 + 1 ] + data[ 0 * 4 + 1 ] * other.data[ 1 * 4 + 1 ] + data[ 0 * 4 + 2 ] * other.data[ 2 * 4 + 1 ] + data[ 0 * 4 + 3 ] * other.data[ 3 * 4 + 1 ],
			data[ 0 * 4 + 0 ] * other.data[ 0 * 4 + 2 ] + data[ 0 * 4 + 1 ] * other.data[ 1 * 4 + 2 ] + data[ 0 * 4 + 2 ] * other.data[ 2 * 4 + 2 ] + data[ 0 * 4 + 3 ] * other.data[ 3 * 4 + 2 ],
			data[ 0 * 4 + 0 ] * other.data[ 0 * 4 + 3 ] + data[ 0 * 4 + 1 ] * other.data[ 1 * 4 + 3 ] + data[ 0 * 4 + 2 ] * other.data[ 2 * 4 + 3 ] + data[ 0 * 4 + 3 ] * other.data[ 3 * 4 + 3 ],
			data[ 1 * 4 + 0 ] * other.data[ 0 * 4 + 0 ] + data[ 1 * 4 + 1 ] * other.data[ 1 * 4 + 0 ] + data[ 1 * 4 + 2 ] * other.data[ 2 * 4 + 0 ] + data[ 1 * 4 + 3 ] * other.data[ 3 * 4 + 0 ],
			data[ 1 * 4 + 0 ] * other.data[ 0 * 4 + 1 ] + data[ 1 * 4 + 1 ] * other.data[ 1 * 4 + 1 ] + data[ 1 * 4 + 2 ] * other.data[ 2 * 4 + 1 ] + data[ 1 * 4 + 3 ] * other.data[ 3 * 4 + 1 ],
			data[ 1 * 4 + 0 ] * other.data[ 0 * 4 + 2 ] + data[ 1 * 4 + 1 ] * other.data[ 1 * 4 + 2 ] + data[ 1 * 4 + 2 ] * other.data[ 2 * 4 + 2 ] + data[ 1 * 4 + 3 ] * other.data[ 3 * 4 + 2 ],
			data[ 1 * 4 + 0 ] * other.data[ 0 * 4 + 3 ] + data[ 1 * 4 + 1 ] * other.data[ 1 * 4 + 3 ] + data[ 1 * 4 + 2 ] * other.data[ 2 * 4 + 3 ] + data[ 1 * 4 + 3 ] * other.data[ 3 * 4 + 3 ],
			data[ 2 * 4 + 0 ] * other.data[ 0 * 4 + 0 ] + data[ 2 * 4 + 1 ] * other.data[ 1 * 4 + 0 ] + data[ 2 * 4 + 2 ] * other.data[ 2 * 4 + 0 ] + data[ 2 * 4 + 3 ] * other.data[ 3 * 4 + 0 ],
			data[ 2 * 4 + 0 ] * other.data[ 0 * 4 + 1 ] + data[ 2 * 4 + 1 ] * other.data[ 1 * 4 + 1 ] + data[ 2 * 4 + 2 ] * other.data[ 2 * 4 + 1 ] + data[ 2 * 4 + 3 ] * other.data[ 3 * 4 + 1 ],
			data[ 2 * 4 + 0 ] * other.data[ 0 * 4 + 2 ] + data[ 2 * 4 + 1 ] * other.data[ 1 * 4 + 2 ] + data[ 2 * 4 + 2 ] * other.data[ 2 * 4 + 2 ] + data[ 2 * 4 + 3 ] * other.data[ 3 * 4 + 2 ],
			data[ 2 * 4 + 0 ] * other.data[ 0 * 4 + 3 ] + data[ 2 * 4 + 1 ] * other.data[ 1 * 4 + 3 ] + data[ 2 * 4 + 2 ] * other.data[ 2 * 4 + 3 ] + data[ 2 * 4 + 3 ] * other.data[ 3 * 4 + 3 ],
			data[ 3 * 4 + 0 ] * other.data[ 0 * 4 + 0 ] + data[ 3 * 4 + 1 ] * other.data[ 1 * 4 + 0 ] + data[ 3 * 4 + 2 ] * other.data[ 2 * 4 + 0 ] + data[ 3 * 4 + 3 ] * other.data[ 3 * 4 + 0 ],
			data[ 3 * 4 + 0 ] * other.data[ 0 * 4 + 1 ] + data[ 3 * 4 + 1 ] * other.data[ 1 * 4 + 1 ] + data[ 3 * 4 + 2 ] * other.data[ 2 * 4 + 1 ] + data[ 3 * 4 + 3 ] * other.data[ 3 * 4 + 1 ],
			data[ 3 * 4 + 0 ] * other.data[ 0 * 4 + 2 ] + data[ 3 * 4 + 1 ] * other.data[ 1 * 4 + 2 ] + data[ 3 * 4 + 2 ] * other.data[ 2 * 4 + 2 ] + data[ 3 * 4 + 3 ] * other.data[ 3 * 4 + 2 ],
			data[ 3 * 4 + 0 ] * other.data[ 0 * 4 + 3 ] + data[ 3 * 4 + 1 ] * other.data[ 1 * 4 + 3 ] + data[ 3 * 4 + 2 ] * other.data[ 2 * 4 + 3 ] + data[ 3 * 4 + 3 ] * other.data[ 3 * 4 + 3 ] 
		);
	}

	// Setting and resetting
	inline void Set( const Matrix4& other )
	{
		Set(
			other.data[  0 ], other.data[  1 ], other.data[  2 ], other.data[  3 ],
			other.data[  4 ], other.data[  5 ], other.data[  6 ], other.data[  7 ],
			other.data[  8 ], other.data[  9 ], other.data[ 10 ], other.data[ 11 ],
			other.data[ 12 ], other.data[ 13 ], other.data[ 14 ], other.data[ 15 ]
		);
	}
	inline void Set( float x0, float x1, float x2, float x3,
						float y0, float y1, float y2, float y3,
						float z0, float z1, float z2, float z3,
						float w0, float w1, float w2, float w3 )
	{
		data[  0 ] = x0; data[  4 ] = y0; data[  8 ] = z0; data[ 12 ] = w0;
		data[  1 ] = x1; data[  5 ] = y1; data[  9 ] = z1; data[ 13 ] = w1;
		data[  2 ] = x2; data[  6 ] = y2; data[ 10 ] = z2; data[ 14 ] = w2;
		data[  3 ] = x3; data[  7 ] = y3; data[ 11 ] = z3; data[ 15 ] = w3;
	}
	inline void SetIdentity()
	{
		Set( 
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// String format for debugging/console output
	inline const std::string ToString() const
	{
		std::stringstream stringStream;
		stringStream
			<< "Matrix4x4" << std::endl
			<< "[" << data[  0 ] << ", " << data[  4 ] << ", " << data[  8 ] << ", " << data[ 12 ] << "]" << std::endl
			<< "[" << data[  1 ] << ", " << data[  5 ] << ", " << data[  9 ] << ", " << data[ 13 ] << "]" << std::endl
			<< "[" << data[  2 ] << ", " << data[  6 ] << ", " << data[ 10 ] << ", " << data[ 14 ] << "]" << std::endl
			<< "[" << data[  3 ] << ", " << data[  7 ] << ", " << data[ 11 ] << ", " << data[ 15 ] << "]" << std::endl;
		return stringStream.str();
	}

	// Operator overloads
	inline const Matrix4 operator * ( float rhs ) const
	{
		return Multiply( rhs );
	}
	inline const Matrix4 operator / ( float rhs ) const
	{
		return DivideBy( rhs );
	}
	inline const Vector3 operator * ( const Vector3& rhs ) const
	{
		return Multiply( rhs );
	}
	inline const Matrix4 operator * ( const Matrix4& rhs ) const
	{
		return Multiply( rhs );
	}
	inline const Matrix4& operator *= ( float rhs )
	{
		Set( Multiply( rhs ) );
		return *this;
	}
	inline const Matrix4& operator *= ( const Matrix4& rhs )
	{
		Set( Multiply( rhs ) );
		return *this;
	}
	inline const Matrix4& operator /= ( float rhs )
	{
		Set( DivideBy( rhs ) );
		return *this;
	}
	inline const Matrix4& operator = ( const Matrix4& rhs )
	{
		Set( rhs );
		return *this;
	}

	// Friends
	// Technically we're overloading the float primitive here, so this is a bit tricky...
	friend inline const Matrix4 operator * ( float lhs, const Matrix4& rhs )
	{
		return rhs.Multiply( lhs );
	}

	// Static
	static inline const Matrix4 Identity()
	{
		return Matrix4();
	}
	static inline const Matrix4 Orthographic( float xMin, float xMax,
												float yMin, float yMax,
												float zMin = -1.0f, float zMax = -1.0f )
	{
		Matrix4 scale = Matrix4::Scale(
			2.0f / ( xMax - xMin ),
			2.0f / ( yMax - yMin ),
			-2.0f / ( zMax - zMin )
		);
		Matrix4 translate = Matrix4::Translate(
			-( xMax + xMin ) / ( xMax - xMin ),
			-( yMax + yMin ) / ( yMax - yMin ),
			-( zMax + zMin ) / ( zMax - zMin )
		);
		return scale * translate;
	}
	static inline const Matrix4 Scale( float factor )
	{
		return Scale( factor, factor, factor );
	}
	static inline const Matrix4 Scale( float x, float y, float z )
	{
		return Matrix4(
			x,    0.0f, 0.0f, 0.0f,
			0.0f, y,    0.0f, 0.0f,
			0.0f, 0.0f, z,    0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	static inline const Matrix4 Translate( float x, float y, float z = 0.0f )
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x,    y,    z,    1.0f
		);
	}
	static inline const Matrix4 ViewportNDC( int width, int height )
	{
		float minZ = 0.0f;
		float maxZ = 1.0f;

		Matrix4 scale1 = Matrix4::Scale(
			1.0f,
			-1.0f,
			1.0f
		);
		Matrix4 scale2 = Matrix4::Scale(
			float( width ) / 2.0f,
			float( height ) / 2.0f,
			maxZ - minZ
		);
		Matrix4 translate = Matrix4::Translate(
			float( width ) / 2.0f,
			float( height ) / 2.0f,
			minZ
		);

		return scale1 * scale2 * translate;
	}
};