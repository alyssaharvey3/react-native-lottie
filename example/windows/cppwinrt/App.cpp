#include "pch.h"

#include "App.h"

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/LottieReactNative.h>

#include "Animations/AnimatedVisuals.HamburgerArrow.h"

namespace winrt {
    using namespace winrt::Windows::UI::Xaml;
    using namespace winrt::Windows::ApplicationModel;
    using namespace winrt::Windows::ApplicationModel::Activation;
}

namespace winrt::Example::implementation {

    /// <summary>
    /// Map animation names to the codegen'd implementation. In the future, the creation of this mapping could itself
    /// be autogenerated by a build step.
    /// </summary>
    struct LottieSourceProvider : winrt::implements<LottieSourceProvider, winrt::LottieReactNative::ILottieSourceProvider>
    {
        LottieSourceProvider() = default;

        winrt::Microsoft::UI::Xaml::Controls::IAnimatedVisualSource GetSourceFromName(winrt::hstring name) {
            if (name == L"Hamburger Arrow" || name == L"Hamburger Arrow (200 px)") {
                return winrt::AnimatedVisuals::HamburgerArrow();
            } else if (name == L"Line Animation") {
                return winrt::AnimatedVisuals::LineAnimation();
            } else if (name == L"Lottie Logo 1") {
                return winrt::AnimatedVisuals::LottieLogo1();
            } else if (name == L"Lottie Logo 2") {
                return winrt::AnimatedVisuals::LottieLogo2();
            } else if (name == L"Lottie Walkthrough") {
                return winrt::AnimatedVisuals::LottieWalkthrough();
            } else if (name == L"Pin Jump") {
                return winrt::AnimatedVisuals::PinJump();
            } else if (name == L"Twitter Heart") {
                return winrt::AnimatedVisuals::TwitterHeart();
            } else if (name == L"Watermelon") {
                return winrt::AnimatedVisuals::Watermelon();
            } else if (name == L"Motion Corpse") {
                return winrt::AnimatedVisuals::MotionCorpse_Jrcanest();
            } else if (name == L"9 squares") {
                return winrt::AnimatedVisuals::_9squares_AlBoardman();
            }
            return nullptr;
        }
        winrt::Microsoft::UI::Xaml::Controls::IAnimatedVisualSource GetSourceFromJson(winrt::hstring json) {
            return nullptr;
        }
    };

    /// <summary>
    /// Initializes the singleton application object.  This is the first line of
    /// authored code executed, and as such is the logical equivalent of main() or
    /// WinMain().
    /// </summary>
    App::App() noexcept
    {
#if BUNDLE
        JavaScriptBundleFile(L"index.windows");
        InstanceSettings().UseWebDebugger(false);
        InstanceSettings().UseFastRefresh(false);
#else
        JavaScriptMainModuleName(L"example/js/index");
        InstanceSettings().UseWebDebugger(true);
        InstanceSettings().UseFastRefresh(true);
#endif

#if _DEBUG
        InstanceSettings().EnableDeveloperMenu(true);
#else
        InstanceSettings().EnableDeveloperMenu(false);
#endif

        // RegisterAutolinkedNativeModulePackages(PackageProviders()); // Includes any autolinked modules

        PackageProviders().Append(winrt::LottieReactNative::ReactPackageProvider(winrt::make<LottieSourceProvider>()));

        InitializeComponent();
    }

    void App::OnLaunched(winrt::LaunchActivatedEventArgs const& e) {
        super::OnLaunched(e);

        auto rootView = winrt::Window::Current().Content();
        auto reactRoot = rootView.try_as<Microsoft::ReactNative::ReactRootView>();

        if (reactRoot == nullptr) {
            reactRoot = Microsoft::ReactNative::ReactRootView();
            reactRoot.ReactNativeHost(Host());
            reactRoot.ComponentName(L"example");

            winrt::Window::Current().Content(reactRoot);
        }
    }

}