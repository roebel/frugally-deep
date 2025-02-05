#include "fdeep/fdeep.hpp"
#include <fstream> // looks like we need this too (edit by π)

using namespace fdeep;

void vec_append(std::vector<float>& results, const std::vector<float>& x){
    results.insert(std::end(results), std::begin(x), std::end(x));
    return;
}

int main()
{
    std::ofstream outFile;
    outFile.open("./models/fd_results.bin", std::ios::binary);
    const bool verbose = false;

    const std::vector<float> x_inf_0 = {2.1, -1.2, 3.14, 1.2};
    const std::vector<float> x_inf_1 = {1, 3, -2, 10};
    const std::vector<float> state_0 = {1.1, -2.1};
    const std::vector<float> state_1 = {2.7, 3.1};
    const std::vector<float> state_2 = {-2.5, 3.0};
    const std::vector<float> state_3 = {-2.0, -10.0};
    std::vector<float> all_results = {};
    std::vector<float> one_result = {};

    const shared_float_vec xt0(fplus::make_shared_ref<float_vec>(x_inf_0));
    const shared_float_vec xt1(fplus::make_shared_ref<float_vec>(x_inf_1));
    const shared_float_vec st0(fplus::make_shared_ref<float_vec>(state_0));
    const shared_float_vec st1(fplus::make_shared_ref<float_vec>(state_1));
    const shared_float_vec st2(fplus::make_shared_ref<float_vec>(state_2));
    const shared_float_vec st3(fplus::make_shared_ref<float_vec>(state_3));

    const tensor5 test_in_0(shape5(1, 1, 1, 4, 1), xt0);
    const tensor5 test_in_1(shape5(1, 1, 1, 4, 1), xt1);
    const tensor5 test_state_0(shape5(1, 1, 1, 1, 2), st0);
    const tensor5 test_state_1(shape5(1, 1, 1, 1, 2), st1);
    const tensor5 test_state_2(shape5(1, 1, 1, 1, 2), st2);
    const tensor5 test_state_3(shape5(1, 1, 1, 1, 2), st3);

    // *********** TEST 1: "GRU_nonstateful_no_init_state.json" ***********
    auto model = load_model("./models/GRU_nonstateful_no_init_state.json");
    /// state_reset = true
    auto result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 2: "GRU_nonstateful_init_state.json" ***********
    model = load_model("./models/GRU_nonstateful_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1, test_state_0});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 3: "GRU_stateful_no_init_state.json" ***********
    model = load_model("./models/GRU_stateful_no_init_state.json");
    /// state_reset = true fdr =
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 4: "GRU_stateful_init_state.json" ***********
    model = load_model("./models/GRU_stateful_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0, test_state_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1, test_state_0});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 5: "LSTM_nonstateful_no_init_state.json" ***********
    model = load_model("./models/LSTM_nonstateful_no_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 6: "LSTM_nonstateful_init_state.json" ***********
    model = load_model("./models/LSTM_nonstateful_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 7: "LSTM_stateful_no_init_state.json" ***********
    model = load_model("./models/LSTM_stateful_no_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 8: "LSTM_stateful_init_state.json" ***********
    model = load_model("./models/LSTM_stateful_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());

    // ************************* BIDIRECTIONAL TESTS ************************* //

    // *********** TEST 9: "bidi-GRU_nonstateful_no_init_state.json" ***********
    model = load_model("./models/bidi-GRU_nonstateful_no_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 10: "bidi-GRU_nonstateful_init_state.json" ***********
    model = load_model("./models/bidi-GRU_nonstateful_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 11: "bidi-GRU_stateful_no_init_state.json" ***********
    model = load_model("./models/bidi-GRU_stateful_no_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 12: "bidi-GRU_stateful_init_state.json" ***********
    model = load_model("./models/bidi-GRU_stateful_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 13: "bidi-LSTM_nonstateful_no_init_state.json" ***********
    model = load_model("./models/bidi-LSTM_nonstateful_no_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 14: "bidi-LSTM_nonstateful_init_state.json" ***********
    model = load_model("./models/bidi-LSTM_nonstateful_init_state.json");
    /// state_reset = true
    result = model.predict({test_in_0, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict({test_in_1, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict({test_in_0, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict({test_in_1, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 15: "bidi-LSTM_stateful_no_init_state.json" ***********
    model = load_model("./models/bidi-LSTM_stateful_no_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1});
    vec_append(all_results, *result[0].as_vector());

    // *********** TEST 16: "bidi-LSTM_stateful_init_state.json" ***********
    model = load_model("./models/bidi-LSTM_nonstateful_init_state.json");
    /// state_reset = true
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    model.reset_states();
    /// state_reset = false
    result = model.predict_stateful({test_in_0, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());
    result = model.predict_stateful({test_in_1, test_state_0, test_state_1, test_state_2, test_state_3});
    vec_append(all_results, *result[0].as_vector());

    if(verbose){
        std::cout << "\n\nOUTPUT ***" << std::endl;
            for(size_t idx = 0; idx < all_results.size(); ++ idx){
                std::cout << all_results[idx] << std::endl;
        }
    }

    const size_t sz = all_results.size();
    // outFile.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    outFile.write(reinterpret_cast<const char*>(&all_results[0]), sz * sizeof(all_results[0]));
    outFile.close();
}