
#include <ranges>
#include <filesystem>

#include <utils/graphics/image.h>

#include <utils/MS/graphics/dx.h>
#include <utils/MS/graphics/text/format.h>
#include <utils/MS/graphics/text/renderer.h>

#include <utils/MS/raw/graphics/text/custom_renderer.h>

const auto lipshort{"Lorem ipsum odor amet, consectetuer adipiscing elit. Etiam phasellus bibendum aenean nisl aliquet egestas natoque nisl. Nibh dis tincidunt euismod eleifend risus fermentum aenean. Lorem inceptos felis fermentum vehicula nullam blandit fusce ultrices. Turpis vulputate tristique; torquent nisl mus facilisis. Malesuada mollis felis donec leo quis. Aliquet feugiat vel consequat; nulla vestibulum morbi sollicitudin nisi."};
const auto lipslong
	{
	R"(
	Lorem ipsum odor amet, consectetuer adipiscing elit. Etiam phasellus bibendum aenean nisl aliquet egestas natoque nisl. Nibh dis tincidunt euismod eleifend risus fermentum aenean. Lorem inceptos felis fermentum vehicula nullam blandit fusce ultrices. Turpis vulputate tristique; torquent nisl mus facilisis. Malesuada mollis felis donec leo quis. Aliquet feugiat vel consequat; nulla vestibulum morbi sollicitudin nisi.
	Urna metus arcu per sagittis urna. Interdum nostra cras habitasse eget mus nascetur, vehicula quis turpis. Vel enim pretium orci fermentum faucibus sociosqu nisl. Pellentesque habitant nostra diam orci vulputate. Vel accumsan leo elit praesent proin mattis. Fringilla porta fames proin fringilla turpis potenti vestibulum. Magna facilisis eros vestibulum facilisis vehicula porta elit efficitur rhoncus. Malesuada congue eros placerat volutpat etiam ad dolor placerat leo.
	Torquent curae sagittis nostra, ipsum vel tortor nulla fames. Consectetur magnis gravida natoque magnis varius curae cursus. Eu consectetur maecenas, neque amet ultrices ullamcorper habitant consequat neque. Dui nibh montes pulvinar eros at. Diam libero egestas inceptos ultrices mus aenean? Volutpat eros pulvinar eros nunc conubia ex faucibus at.
	Eleifend pretium inceptos felis amet eleifend suspendisse integer congue. Purus vitae augue hendrerit finibus lectus lobortis tempor ex. Lobortis malesuada consectetur morbi euismod metus ullamcorper? Dapibus natoque torquent mauris tempus consequat euismod morbi taciti. Feugiat penatibus duis habitant; arcu metus ultrices erat torquent. Nisi est interdum gravida tristique ad tortor cras.
	Venenatis augue conubia; porta porttitor feugiat viverra viverra. Fames placerat congue sem habitant sollicitudin erat duis! Ante platea nibh urna ad eros ac finibus justo. Turpis urna quisque condimentum, efficitur potenti tincidunt mauris praesent. Magna iaculis nibh fermentum molestie fermentum ex lectus sodales. Sagittis molestie magnis luctus justo cubilia arcu metus imperdiet inceptos. Consectetur libero commodo; pharetra aliquet luctus porttitor.
	)"
	};

int main()
	{
	utils::MS::graphics::dx::initializer dx_initializer;
	utils::MS::graphics::dx::context     dx_context{dx_initializer};

	while(true)
		{
		const utils::graphics::colour::rgba_f background_colour{0.f, .1f, .2f, 1.f};
		const utils::math::vec2s resolution{size_t{512}, size_t{256}};
		const utils::math::vec2f resolution_f{static_cast<float>(resolution.x()), static_cast<float>(resolution.y())};

		utils::MS::graphics::text::format text_format
			{
			.font{"Gabriola"},
			.size{64.f},
			.alignment{.horizontal{utils::alignment::horizontal::centre}}
			};

		utils::MS::graphics::text::renderer text_renderer{dx_initializer, resolution, background_colour};
	
		utils::MS::graphics::text::formatted_string formatted_string{dx_initializer, "Hello Universe!", text_format, {128.f, 32.f}};
	
		formatted_string.properties_regions.rendering.decorators.to_image.add(false, {5, 5});
		formatted_string.properties_regions.rendering.text.colour      .add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 30});
		formatted_string.properties_regions.rendering.outline.colour   .add(utils::graphics::colour::rgba_f{.3f, 1.f, .7f, 1.f}, {0, 30});
		formatted_string.properties_regions.rendering.decorators.colour.add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 11});
		formatted_string.properties_regions.rendering.decorators.colour.add(utils::graphics::colour::rgba_f{1.f, 1.f, 0.f, 1.f}, {2,  3});
		formatted_string.properties_regions.rendering.text.to_image    .add(false                                              , {6,  3});
		formatted_string.properties_regions.rendering.text.colour      .add(utils::graphics::colour::rgba_f{0.f, 1.f, 0.f, 1.f}, {6,  3});
		formatted_string.properties_regions.rendering.outline.to_image .add(true                                               , {6, 15});
		formatted_string.properties_regions.formatting.font.add("Arial", {3, 5});
		formatted_string.properties_regions.formatting.size.add(48.f, {5, 4});
		formatted_string.shrink_to_fit();
		formatted_string.update();

		text_renderer.draw_text(formatted_string, {0.f, 0.f});

		const auto image{text_renderer.get_output().image};

		std::filesystem::create_directories("./output");
		utils::graphics::image::save_to_file(image, "output/test.png");
		}
	}