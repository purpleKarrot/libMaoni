/*
 * A simple sphere mapping shader
 */

#include <Maoni.hpp>
#include "ModelPLY.hpp"

SHADER_SOURCE(vertex_source, (version 120),

		varying vec3 normal;

		void main()
		{
			normal = gl_NormalMatrix * gl_Normal;

			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source, (version 120),

		uniform sampler2D texture;
		varying vec3 normal;

		void main()
		{
			gl_FragColor = texture2D(texture, vec2(0.5) + 0.5 * normalize(normal).xy);
		}
);

SHADER_PROGRAM(SphereMappingShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(SphereMapping,
		(ShaderProgram, shader, SphereMappingShader())
		(Texture, sphere_texture, "../examples/Models/sphere3.jpg")
		(ModelPLY, model, "bunny.ply")
)
{
//	ScopedDisable lighting_lock(GL_LIGHTING);
//	ScopedEnable texture_2D_lock(GL_TEXTURE_2D);
//	ScopedBindTexture texture_lock(sphere_texture, GL_TEXTURE0);
//	ScopedUseProgram shader_lock(shader);
//
//	glUniform1i(glGetUniformLocation(shader, "texture"), 0);

	model.draw(myrank, ranks);
}
