
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
	const utils::graphics::colour::rgba_f background_colour{0.f, .1f, .2f, 1.f};
	const utils::math::vec2s resolution{size_t{512}, size_t{256}};
	const utils::math::vec2f resolution_f{static_cast<float>(resolution.x()), static_cast<float>(resolution.y())};


	utils::MS::graphics::text::format text_format_0
		{
		.font{"Gabriola"},
		.size{64.f},
		.alignment{.horizontal{utils::alignment::horizontal::centre}},
		.colour{utils::graphics::colour::base::white},
		.shrink_to_fit{true}
		};
	utils::MS::graphics::text::format text_format_1
		{
		.font{"Arial"},
		.alignment{.vertical{utils::alignment::vertical::top}},
		.colour{utils::graphics::colour::base::white, .8f},
		.shrink_to_fit{true}
		};

	utils::MS::graphics::text::renderer text_renderer{resolution, background_colour};
	text_renderer.draw_text(text_format_0, "Hello World!", {0.f, 0.f, resolution_f.x(), 64.f});
	text_renderer.draw_text(text_format_1, lipslong, {0.f, 64.f, resolution_f.x(), resolution_f.y()});

	const auto image{text_renderer.get_image()};

	std::filesystem::create_directories("./output");
	utils::graphics::image::save_to_file(image, "output/test.png");




	utils::MS::graphics::dx::initializer dx_initializer;
	utils::MS::graphics::dx::context     dx_context{dx_initializer};
	
	utils::MS::graphics::text::formatted_string formatted_string{"Hello Universe!", text_format_0, resolution_f};

	auto dw_factory {utils::MS::raw::graphics::dw  ::factory::create()};
	auto d3d_device {utils::MS::raw::graphics::d3d ::device ::create()};
	auto dxgi_device{utils::MS::raw::graphics::dxgi::device ::create(d3d_device)};
	auto d2d_factory{utils::MS::raw::graphics::d2d ::factory::create()};
	auto d2d_device {utils::MS::raw::graphics::d2d ::device ::create(d2d_factory, dxgi_device)};
	auto d2d_context{utils::MS::raw::graphics::d2d ::context::create(d2d_device)};
	
	auto brush{utils::MS::raw::graphics::d2d::brush::create(d2d_context, {1.f, .5f, 0.f, 1.f})};
	
	
	
	auto bitmap{utils::MS::raw::graphics::d2d::bitmap::create(d2d_context, utils::MS::raw::graphics::d2d::bitmap::create_info
		{
		.resolution {resolution},
		.dxgi_format{DXGI_FORMAT_R32G32B32A32_FLOAT},
		.alpha_mode {D2D1_ALPHA_MODE_PREMULTIPLIED},
		.options    {D2D1_BITMAP_OPTIONS_TARGET},
		})};
	d2d_context->SetTarget(bitmap.get());
	d2d_context->BeginDraw();
	d2d_context->Clear(utils::MS::raw::graphics::d2d::cast(background_colour));
	d2d_context->EndDraw();
	
	if (true)
		{
		auto renderer{utils::MS::raw::graphics::text::custom_renderer::renderer::create(d2d_factory)};

		auto text_format{utils::MS::raw::graphics::dw::text_format::create(dw_factory, text_format_0)};
		auto text_layout{utils::MS::raw::graphics::dw::text_layout::create(dw_factory, text_format, "Hello-world\nasdQWE", resolution_f)};






		utils::MS::graphics::text::effects_regions er;
		er.decorators_to_image.add(false, {5, 5});
		er.text_colour      .add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 30});
		er.decorators_colour.add(utils::graphics::colour::rgba_f{1.f, 0.f, 0.f, 1.f}, {0, 11});
		er.decorators_colour.add(utils::graphics::colour::rgba_f{1.f, 1.f, 0.f, 1.f}, {2,  3});
		er.text_to_image    .add(false                                              , {6,  3});
		er.text_colour      .add(utils::graphics::colour::rgba_f{0.f, 1.f, 0.f, 1.f}, {6,  3});
		er.outline_to_image .add(true                                               , {6, 15});
		
		const auto effects_regions{er.evaluate_effects_regions()};
		
		for (size_t i{0}; i < effects_regions.slots_size(); i++)
			{
			const auto slot{effects_regions.slot_at(i)};
			if (slot.value_opt_ref.has_value())
				{
				const auto& value{slot.value_opt_ref.value().get()};
		
				auto com_ptr_effects{utils::MS::raw::graphics::text::custom_renderer::effects::create(value)};
				text_layout->SetDrawingEffect(com_ptr_effects.get(), DWRITE_TEXT_RANGE{utils::math::cast_clamp<UINT32>(slot.region.begin), utils::math::cast_clamp<UINT32>(slot.region.count)});
				}
			}

		text_layout->SetUnderline(true, {0, 20});

		utils::MS::raw::graphics::text::custom_renderer::contexts contexts{.render_context{d2d_context}};
		
		d2d_context->BeginDraw();
		
		text_layout->Draw(&contexts, renderer.get(), 0.f, 0.f);
		d2d_context->EndDraw  ();
		}
	
	const auto cpu_image{utils::MS::raw::graphics::d2d::bitmap::to_cpu_matrix(bitmap, d2d_context)};
	utils::graphics::image::save_to_file(cpu_image, "output/test2.png");
	}