#include <iostream>
#include <chrono>

#include <utils/enum.h>

#include <utils/MS/graphics/dx/initializer.h>
#include <utils/MS/graphics/dx/initializer/exposed_MS.h>
#include <utils/MS/window/window.h>
#include <utils/MS/window/style.h>
#include <utils/MS/window/regions.h>
#include <utils/MS/raw/graphics/d2d.h>
#include <utils/MS/raw/graphics/d2d_window_module.h>
#include <utils/MS/raw/graphics/d2d/cast.h>

#include "all.h"

static void body()
	{
	using namespace utils::output;

	utils::MS::graphics::dx::initializer dx_initializer;

	utils::MS::window::initializer window_initializer;

	winrt::com_ptr<ID2D1Factory6> d2dfv6;
	dx_initializer->d2d_factory->QueryInterface<ID2D1Factory6>(d2dfv6.put());


	std::unique_ptr<int> asd{std::make_unique<int>(3)};
	std::unique_ptr<int> qwe{std::move(asd)};

	//using render_window_module_type = utils::MS::raw::graphics::d2d::window::render_target         ; //transparency, cannot guarantee same device for multiple windows
	//using render_window_module_type = utils::MS::raw::graphics::d2d::window::swap_chain            ; //guarantees same device for multiple windows, no transparency 
	using render_window_module_type = utils::MS::raw::graphics::d2d::window::composition_swap_chain; //should do both but I don't trust I've done it correctly at all lol 

	utils::MS::window::base window
		{
		utils::MS::window::base::create_info{.position{{1024, 768}}, .size{{256u, 128u}}},
		close_module::create_info{},
		utils::MS::window::style::create_info
			{
			.transparency{utils::MS::window::style::transparency_t::composition_attribute},
			.borders{utils::MS::window::style::value_t::disable}
			},
		utils::MS::window::resizable_edge::create_info{.thickness{8}},
		render_window_module_type::create_info
			{
			//.d2d_factory{dx_initializer->d2d_factory}, //uncomment for render_target, since it doesn't take a device
			.d2d_device{dx_initializer->d2d_device}, //uncomment for swap_chain and composition_swap_chain,
			.draw_callback
				{
				[](const utils::MS::window::base& window, ID2D1DeviceContext5* context)
					{
					context->SetTransform(D2D1::IdentityMatrix());
					context->Clear(D2D1_COLOR_F{0.f, 0.f, 0.f, 0.f});

					const auto client_rect_l{window.client_rect};
					const auto client_rect{client_rect_l.cast<float>()};

					utils::math::vec2f size_f      {static_cast<float>(client_rect.width()), static_cast<float>(client_rect.height())};

					namespace umrg = utils::MS::raw::graphics;

					const umrg::d2d::brush_gradient brush_0{context, umrg::d2d::brush_gradient::create_info_simplified{{0.f, 0.f}, {100.f, 100.f}, {{1.f, 0.f, 0.f, .2f}, {1.f, 1.f, 0.f, .2f}, {0.f, 1.f, 0.f, 0.2f}, {0.f, 1.f, 1.f, 0.2f}, {0.f, 0.f, 1.f, 0.2f}}}};
					const umrg::d2d::brush_gradient brush_r{context, umrg::d2d::brush_gradient::create_info_simplified{{0.f, 0.f}, {100.f, 100.f}, {{1.f, 0.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 0.1f}, {1.f, 0.f, 0.f, 0.5f}, {1.f, 0.f, 0.f, 1.f}}}};
					const umrg::d2d::brush_gradient brush_g{context, umrg::d2d::brush_gradient::create_info_simplified{{0.f, 0.f}, {100.f, 100.f}, {{0.f, 1.f, 0.f, 0.f}, {0.f, 1.f, 0.f, 0.1f}, {0.f, 1.f, 0.f, 0.5f}, {0.f, 1.f, 0.f, 1.f}}}};
					const umrg::d2d::brush_gradient brush_b{context, umrg::d2d::brush_gradient::create_info_simplified{{0.f, 0.f}, {100.f, 100.f}, {{0.f, 0.f, 1.f, 0.f}, {0.f, 0.f, 1.f, 0.1f}, {0.f, 0.f, 1.f, 0.5f}, {0.f, 0.f, 1.f, 1.f}}}};
					const umrg::d2d::brush_gradient brush_y{context, umrg::d2d::brush_gradient::create_info_simplified{{0.f, 0.f}, {100.f, 100.f}, {{1.f, 1.f, 0.f, 0.f}, {1.f, 1.f, 0.f, 0.1f}, {1.f, 1.f, 0.f, 0.5f}, {1.f, 1.f, 0.f, 1.f}}}};


					const utils::math::vec2f coords_0{0.f, 0.f         };
					const utils::math::vec2f coords_1{[&]() { const auto tmp{size_f / 4.f     }; return tmp.for_each_to_new([](const float& value){return std::floor(value);}); }()};
					const utils::math::vec2f coords_2{[&]() { const auto tmp{size_f / 2.f     }; return tmp.for_each_to_new([](const float& value){return std::floor(value);}); }()};
					const utils::math::vec2f coords_3{[&]() { const auto tmp{size_f - coords_1}; return tmp.for_each_to_new([](const float& value){return std::floor(value);}); }()};
					const utils::math::vec2f coords_4{[&]() { const auto tmp{size_f           }; return tmp.for_each_to_new([](const float& value){return std::floor(value);}); }()};

					context->FillRectangle({coords_0.x(), coords_0.y(), coords_2.x(), coords_1.y()}, brush_r.get());
					context->FillRectangle({coords_0.x(), coords_1.y(), coords_1.x(), coords_2.y()}, brush_r.get());

					context->FillRectangle({coords_4.x(), coords_0.y(), coords_2.x(), coords_1.y()}, brush_g.get());
					context->FillRectangle({coords_4.x(), coords_1.y(), coords_3.x(), coords_2.y()}, brush_g.get());

					context->FillRectangle({coords_0.x(), coords_4.y(), coords_2.x(), coords_3.y()}, brush_b.get());
					context->FillRectangle({coords_0.x(), coords_3.y(), coords_1.x(), coords_2.y()}, brush_b.get());

					context->FillRectangle({coords_4.x(), coords_4.y(), coords_2.x(), coords_3.y()}, brush_y.get());
					context->FillRectangle({coords_4.x(), coords_3.y(), coords_3.x(), coords_2.y()}, brush_y.get());

					context->FillRectangle({coords_1.x(), coords_1.y(), coords_3.x(), coords_3.y()}, brush_0.get());
					}
				}
			}
		};

	auto graphics_module_ptr{window.get_module_ptr<render_window_module_type>()};


	window.show();
	while (window.is_open())
		{
		/*
		window.wait_event();
		/*/
		while (window.poll_event());
		graphics_module_ptr->draw();
		/**/
		}
	}

void example::window::drawing_system()
	{
	try { body(); }
	catch (const std::exception & e) { std::cout << e.what() << std::endl; }
	}