
#include <ranges>
#include <filesystem>

#include <utils/graphics/image.h>

#include <utils/MS/graphics/dx.h>
#include <utils/MS/graphics/text/format.h>
#include <utils/MS/graphics/text/renderer.h>

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

	const utils::graphics::colour::rgba_f background_colour{0.f, .1f, .2f, 1.f};
	const utils::math::vec2s resolution{size_t{512}, size_t{256}};
	const utils::math::vec2f resolution_f{static_cast<float>(resolution.x()), static_cast<float>(resolution.y())};

	utils::MS::graphics::text::format text_format
		{
		.font{"Gabriola"},
		.size{96.f},
		.alignment{.horizontal_alignment{utils::alignment::horizontal::centre}}
		};

	utils::MS::graphics::text::renderer text_renderer{dx_initializer, utils::MS::graphics::text::renderer::create_info{.resolution{resolution}, .clear_colour{background_colour}}};
	
	utils::MS::graphics::text::formatted_string formatted_string{u"Hello Universe!", text_format, {512.f, 256.f}};

	formatted_string.properties_regions.render.fill         .to_image.reset(true);
	formatted_string.properties_regions.render.outline      .to_image.reset(true);
	formatted_string.properties_regions.render.underline    .to_image.reset(true);
	formatted_string.properties_regions.render.rect         .to_image.reset(true);
	formatted_string.properties_regions.render.strikethrough.to_image.reset(true);

	formatted_string.properties_regions.format.fill         .enabled.add(false, {6,  3});
	formatted_string.properties_regions.format.outline      .enabled.add(true , {6, 15});
	formatted_string.properties_regions.format.underline    .enabled.add(true , {5,  5});
	formatted_string.properties_regions.format.underline    .enabled.add(true , {6,  5});
	formatted_string.properties_regions.format.strikethrough.enabled.add(true , {5,  5});
	formatted_string.properties_regions.format.strikethrough.enabled.add(true , {6,  5});

	formatted_string.properties_regions.format.fill         .colour.add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 30});
	formatted_string.properties_regions.format.fill         .colour.add(utils::graphics::colour::rgba_f{0.f, 1.f, 0.f, 1.f}, {3,  3});
	formatted_string.properties_regions.format.outline      .colour.add(utils::graphics::colour::rgba_f{.3f, 1.f, .7f, 1.f}, {0, 30});
	formatted_string.properties_regions.format.underline    .colour.add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 11});
	formatted_string.properties_regions.format.underline    .colour.add(utils::graphics::colour::rgba_f{1.f, 1.f, 0.f, 1.f}, {2,  3});
	formatted_string.properties_regions.format.strikethrough.colour.add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 11});
	formatted_string.properties_regions.format.strikethrough.colour.add(utils::graphics::colour::rgba_f{1.f, 1.f, 0.f, 1.f}, {2,  3});
	formatted_string.properties_regions.format.font.add("Arial", {3, 5});
	formatted_string.properties_regions.format.size.add(48.f, {5, 4});

	const auto renderable{formatted_string.shrink_to_fit(dx_initializer)};

	text_renderer.draw_text(renderable, {0.f, 0.f});

	const auto image{text_renderer.get_output_image()};

	std::filesystem::create_directories("./output");
	utils::graphics::image::save_to_file(image, "output/test.png");
	}